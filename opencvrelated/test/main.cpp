#include <stdio.h>
#include "cv.h"
#include "highgui.h"

CvHaarClassifierCascade *cascade;
CvMemStorage            *storage;

void detectFaces( IplImage *img );

int main( int argc, char** argv )
{
    IplImage  *frame;
    int       key;
    char      *filename = "haarcascade_frontalface_alt.xml";
    cascade = ( CvHaarClassifierCascade* )cvLoad( filename, 0, 0, 0 );
   
    storage = cvCreateMemStorage( 0 );
    cvNamedWindow( "face-detection", 1 );
    frame = cvLoadImage(argv[1]);
    detectFaces( frame );
    cvWaitKey( 0 );
    cvDestroyWindow( "face-detection" );
    cvReleaseHaarClassifierCascade( &cascade );
    cvReleaseMemStorage( &storage );
    return 0;
}

void detectFaces( IplImage *img )
{
    int i;
    CvSeq *faces = cvHaarDetectObjects(img,cascade, storage,1.1,3,0,cvSize( 40, 40 ) );
    for( i = 0 ; i < ( faces ? faces->total : 0 ) ; i++ ) {
     CvRect *r = ( CvRect* )cvGetSeqElem( faces, i );
     cvRectangle( img,
     cvPoint( r->x, r->y ),
     cvPoint( r->x + r->width, r->y + r->height ),
     CV_RGB( 255, 0, 0 ), 1, 8, 0 );
    }
    cvShowImage( "face-detection", img );
}
