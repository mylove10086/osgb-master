#include <stdio.h>
#include <stdlib.h>
#include "../jpeglib.h"


int main(int argc, char **argv) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    int row_stride;
    FILE *fille = fopen("../dome/a1.jpeg", "rb");
    fseek(fille, 0, SEEK_END);// 移动到文件末尾
    long int size = ftell(fille);
    fseek(fille, 0, SEEK_SET);// 移动到文件开头
    unsigned char *buffer = (unsigned char *) malloc(size);
    size_t byteread = fread(buffer, sizeof(unsigned char), size, fille);


    // 分配和初始化一个decompression结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    //jpeg_stdio_src(&cinfo, infile);// 读文件
    jpeg_mem_src(&cinfo,buffer,size);// 从内存中解析
    // 用jpeg_read_header获得jpg信息
    jpeg_read_header(&cinfo, TRUE);
    (void) jpeg_start_decompress(&cinfo);

    /* 源信息 */
    printf("image_width = %d\n", cinfo.image_width);
    printf("image_height = %d\n", cinfo.image_height);
    printf("num_components = %d\n", cinfo.num_components);
    // 一行的数据长度
    row_stride = cinfo.image_width * cinfo.num_components;
    unsigned char * buffer1 = malloc(row_stride*cinfo.image_height);//分配空间用来存储一行数据
    //(void) jpeg_read_scanlines(&cinfo, &buffer1, cinfo.image_height);

    // 循环调用jpeg_read_scanlines来一行一行地获得解压的数据
    while (cinfo.output_scanline < cinfo.image_height) {
        (void) jpeg_read_scanlines(&cinfo, &buffer1, 1);
    }

    free(buffer);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return 0;
}
