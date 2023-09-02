#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>


int main(int argc, char **argv) {
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *infile;
    int row_stride;
    unsigned char *buffer;

    if (argc != 2) {
        printf("Usage: \n");
        printf("%s <jpg_file>\n", argv[0]);
        return -1;
    }


    // 分配和初始化一个decompression结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    char url[]="../dome/a1.jpeg";
    // 指定源文件
    if ((infile = fopen(url, "rb")) == NULL) {
        fprintf(stderr, "can't open %s\n", argv[1]);
        return -1;
    }
    jpeg_stdio_src(&cinfo, infile);

    // 用jpeg_read_header获得jpg信息
    jpeg_read_header(&cinfo, TRUE);
    /* 源信息 */
    printf("image_width = %d\n", cinfo.image_width);
    printf("image_height = %d\n", cinfo.image_height);
    printf("num_components = %d\n", cinfo.num_components);

    // 设置解压参数,比如放大、缩小
    printf("enter scale M/N:\n");
    scanf("%d/%d", &cinfo.scale_num, &cinfo.scale_denom);
    printf("scale to : %d/%d\n", cinfo.scale_num, cinfo.scale_denom);

    // 启动解压：jpeg_start_decompress
    jpeg_start_decompress(&cinfo);

    /* 输出的图象的信息 */
    printf("output_width = %d\n", cinfo.output_width);
    printf("output_height = %d\n", cinfo.output_height);
    printf("output_components = %d\n", cinfo.output_components);//解压的是rgb，故为3元素

    // 一行的数据长度
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = malloc(row_stride);//分配空间用来存储一行数据

    // 循环调用jpeg_read_scanlines来一行一行地获得解压的数据
    while (cinfo.output_scanline < cinfo.output_height) {
        (void) jpeg_read_scanlines(&cinfo, &buffer, 1);

    }

    free(buffer);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return 0;
}
