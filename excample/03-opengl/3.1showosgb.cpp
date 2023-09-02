#include <iostream>
#include <fstream>
#include <vector>
#include <Geometry.h>
#include <Osgb.h>
#include "Drawable.h"
#include <stdio.h>
#include "jpeglib.h"

using namespace osg;

void saveJpeg(std::string filename, unsigned char *bits, int width, int height, int depth) {
    //https://www.cnblogs.com/SunkingYang/p/11049160.html
    FILE *outfile;                 /* target file */
    outfile = fopen(filename.c_str(), "wb");

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;      /* image width and height, in pixels */
    cinfo.image_height = height;
    cinfo.input_components = 3;         /* # of color components per pixel */
    cinfo.in_color_space = JCS_RGB;         /* colorspace of input image */

    jpeg_set_defaults(&cinfo);
    int m_quality = 100;
    jpeg_set_quality(&cinfo, m_quality, TRUE /* limit to baseline-JPEG values */);

    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];        /* pointer to JSAMPLE row[s] */
    int row_stride;             /* physical row width in image buffer */
    row_stride = width * depth; /* JSAMPLEs per row in image_buffer */

    while (cinfo.next_scanline < cinfo.image_height) {
        //这里我做过修改，由于jpg文件的图像是倒的，所以改了一下读的顺序
        //row_pointer[0] = & bits[cinfo.next_scanline * row_stride];
        row_pointer[0] = &bits[(cinfo.image_height - cinfo.next_scanline - 1) * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);

    jpeg_destroy_compress(&cinfo);

}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string fileurl = "../data/1536.terrain";
    fileurl = "../data/Tile_11_L24_00100000.osgb";
    fileurl = "../data/Tile_+002_+002/Tile_+002_+002_L17_000.osgb";
    fileurl = "../data/osgb/Tile_+002_+002/Tile_+002_+002_L20_000120.osgb";
    std::vector<float> *vo = new std::vector<float>();
    vo->push_back(1.0);
    vo->at(0) = 2.0;


    Osgb osgb;
    osgb.read(fileurl);
    osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data;
    size_t size = osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data.size();
    FILE *file = fopen("../data/test.jpeg", "wb");
    fwrite(&(osgb.pagedLod[0]->geode[0]->geometry->_drawable->_stateSet->_texture[0]->_image->data)[0],
           sizeof(unsigned char), size, file);
    fclose(file);
    //saveJpeg("../data/test.jpeg",);
    return 0;
}
