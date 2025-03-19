#include "camera.h"

camera::camera(bool *mark_camera,QLabel *lb)
{
    mark=mark_camera;
    l=lb;

    lcdfd=0;//LCD 设备的文件描述符
    lcdptr=NULL;//LCD 内存映射指针

    //默认的 LCD 宽度和高度
    lcd_w=800;
    lcd_h=480;

    QPixmap map("/nfs/my.jpg"); // 初次加载图片
    l->setPixmap(map); //设置标签显示图片
    l->setScaledContents(true); // 设置标签内容自适应图片大小

}

int camera::read_JPEG_file (unsigned char *jpegData,unsigned char *rgbdata, int size)
{
    struct jpeg_error_mgr jerr;
    struct jpeg_decompress_struct cinfo;
    cinfo.err = jpeg_std_error(&jerr);

    // 创建解码对象并且初始化
    jpeg_create_decompress(&cinfo);

    // 装备解码的数据（采用内存作为数据源）

    //指定 JPEG 数据来源为内存缓冲区，这里传入 jpegData 和其长度 size。
    jpeg_mem_src(&cinfo,(unsigned char *)jpegData, size);
    
    // 读取JPEG文件头，获得图片参数
    (void) jpeg_read_header(&cinfo, TRUE);

    // 开始解码过程
    (void) jpeg_start_decompress(&cinfo);

    // 计算每一行的字节数：宽度 * 每个像素的分量数
    int row_stride = cinfo.output_width * cinfo.output_components;

    // 为存放一行数据申请内存
    unsigned char *buffer = (unsigned char *)malloc(row_stride);

    int i=0;
    // 循环读取每一行扫描线，直到全部读取完毕
    while (cinfo.output_scanline < cinfo.output_height) 
    {
        //printf()<<("****%d\n",i);
        // 读取一行数据到 buffer 中
        (void) jpeg_read_scanlines(&cinfo, &buffer, 1);
        // 将读取到的数据复制到目标缓冲区中
        memcpy(rgbdata+i*640*3, buffer, row_stride );
        i++;
    }

    //解码完成
    (void) jpeg_finish_decompress(&cinfo);

    //释放解码对象
    jpeg_destroy_decompress(&cinfo);

    return 1;
}

void camera::lcd_show_rgb(unsigned char *rgbdata,int w,int h,int size)
{
    std::vector<unsigned char >jpegData;
    jpegData.reserve(size);
    //int dataSize = jpegData.size();

    // 将原始数据拷贝到 vector 中
    std::copy(rgbdata,rgbdata+size,std::back_inserter(jpegData));
    QImage image;
    // 尝试从内存数据中加载图像
    if (image.loadFromData(jpegData.data(), size)) 
    {
        // 图像加载成功
        QPixmap pixmap = QPixmap::fromImage(image);
        l->setPixmap(pixmap);
        l->setScaledContents(true); // 根据需要调整
        l->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        l->show();

    }else
    {
        printf("show failed\n");
    }
    QThread::msleep(20);
}

void camera::rel_han6()
{
    lcdfd=open("/dev/fb0",O_RDWR);

    struct fb_var_screeninfo info;
    int lret = ioctl(lcdfd,FBIOGET_VSCREENINFO,&info);
    //虚拟机
    lcd_w=info.xres_virtual;
    lcd_h=info.yres_virtual;
    //arm
    // lcd_w=info.xres;
    // lcd_h=info.yres;
    //映射LCD设备到内存
    lcdptr=(unsigned int *)mmap(NULL,lcd_w*lcd_h*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
    
    //1.打开设备
    int fd = ::open("/dev/video0",O_RDWR);
    if (fd < 0)
    {
        perror("打开摄像头设备失败");
        return ;
    }else{
        qDebug()<<"open /dev/video0 success";
    }

    //2.获取摄像头支持的格式
    struct v4l2_fmtdesc v4fmt;
    v4fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;//视频采集
    int i=0;
    while(1)
    {
        v4fmt.index = i++;
        int ret = ioctl(fd, VIDIOC_ENUM_FMT, &v4fmt);
        if(ret < 0)
        {
            perror("摄像头支持的格式获取失败");
            break;
        }else
        {
            printf("摄像头支持的格式获取成功\n");
            printf("index=%d\n", v4fmt.index);
            printf("flags=%d\n", v4fmt.flags);
            printf("description=%s\n", v4fmt.description);
            unsigned char *p = (unsigned char *)&v4fmt.pixelformat;
            printf("pixelformat=%c%c%c%c\n", p[0],p[1],p[2],p[3]);
            printf("reserved=%d\n", v4fmt.reserved[0]);
        }
    }

    //3.设置采集格式
    struct v4l2_format vfmt;
    vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;//摄像头采集
    vfmt.fmt.pix.width = 640;//设置宽（不能任意）
    vfmt.fmt.pix.height = 480;//设置高
    vfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;//设置视频采集格式
    int ret = ioctl(fd, VIDIOC_S_FMT, &vfmt);
    if(ret < 0)
    {
        perror("设置格式失败");
    }

    //----------
    memset(&vfmt, 0, sizeof(vfmt));
    vfmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret  = ioctl(fd, VIDIOC_G_FMT, &vfmt);
    if(ret < 0)
    {
        perror("获取格式失败");
    }

    if(vfmt.fmt.pix.width == 640 && vfmt.fmt.pix.height == 480 &&
    vfmt.fmt.pix.pixelformat == V4L2_PIX_FMT_JPEG)
    {
        printf("设置成功\n");
    }else
    {
        printf("设置失败\n");
    }
    //----------

    //4.申请内核空间
    struct v4l2_requestbuffers reqbuffer;
    reqbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuffer.count = 4; //申请4个缓冲区
    reqbuffer.memory = V4L2_MEMORY_MMAP ;//映射方式
    ret  = ioctl(fd, VIDIOC_REQBUFS, &reqbuffer);
    if(ret < 0)
    {
        perror("申请队列空间失败");
    }else
    printf("申请队列空间成功\n");

    //5.映射
    unsigned char *mptr[4];//保存映射后用户空间的首地址
    unsigned int  size[4];
    struct v4l2_buffer mapbuffer;
    //初始化type, index
    mapbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    for(i=0; i<4; i++)
    {
        mapbuffer.index = i;
        ret = ioctl(fd, VIDIOC_QUERYBUF, &mapbuffer);//从内核空间中查询一个空间做映射
        if(ret < 0)
        {
            perror("查询内核空间队列失败");
        }
        mptr[i] = (unsigned char *)mmap(NULL, mapbuffer.length, PROT_READ|PROT_WRITE,
                                            MAP_SHARED, fd, mapbuffer.m.offset);
        size[i]=mapbuffer.length;

        // 将每个映射完成的缓冲区放回到内核队列
        ret  = ioctl(fd, VIDIOC_QBUF, &mapbuffer);
        if(ret < 0)
        {
            perror("放回失败");
        }
    }

    //6.开始采集
    int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ret = ioctl(fd, VIDIOC_STREAMON, &type);
    if(ret < 0)
    {
        perror("开启失败");
    }else
    {
        printf("开启成功\n");
    }

    unsigned char rgbdata[640*480*3];
    struct v4l2_buffer readbuffer;
    while(*mark)
    {
        memset(&readbuffer,0,sizeof(struct v4l2_buffer));
        // 从队列中提取一帧数据
        readbuffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        //	readbuffer.index=1;
        readbuffer.memory = V4L2_MEMORY_MMAP;
        ret = ioctl(fd, VIDIOC_DQBUF, &readbuffer);
        if(ret < 0)
        {
            perror("提取数据失败");
        }

        read_JPEG_file(mptr[readbuffer.index],rgbdata,readbuffer.length);
        //lcd_show_rgb(rgbdata,640,480);
        lcd_show_rgb(mptr[readbuffer.index],640,480,readbuffer.length);

        //通知内核已经使用完毕
        ret = ioctl(fd, VIDIOC_QBUF, &readbuffer);
        if(ret < 0)
        {
            perror("放回队列失败");
        }
    }

    //7.停止采集
    ret = ioctl(fd, VIDIOC_STREAMOFF, &type);

    //8.释放映射
    for(i=0; i<4; i++)
        munmap(mptr[i], size[i]);
    ::close(fd);
}
