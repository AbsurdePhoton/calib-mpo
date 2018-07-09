#include <QPixmap>
#include <QFile>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

bool MPO2Pixmap(QString source, vector<QPixmap>& vector) {
    int count = 0;
    int laufIndex, fileLength;
    int secondImageStart = 0;
    // open MPO file as datastream
    QFile imageFile(source);
    // open if exist
    if (imageFile.exists()) {
        // open file in read only mode
        imageFile.open(QIODevice::ReadOnly);
        QDataStream dataInfilestream(&imageFile);
        // get file length
        fileLength = imageFile.size();
        // define data vector
        QVector<uchar> imageData(fileLength);
        // read data from stream
        while(!dataInfilestream.atEnd()) {
            // copy file bytewise
            dataInfilestream >> imageData[count++];
        }
        // close file
        imageFile.close();
        // search for beginning of second image (normaly at half of the full MPO file)
        for (laufIndex = (int)(fileLength * 0.40); laufIndex < (int)(fileLength * 0.60); laufIndex++) {
            if ((imageData[laufIndex] == 0xFF) && (imageData[laufIndex+1] == 0xD8) \
              && (imageData[laufIndex+2] == 0xFF) && (imageData[laufIndex+3] == 0xE1)) {
                secondImageStart = laufIndex;
                break;
            };
        }
        // if no seperator is found
        if (secondImageStart == 0) {
            return false;
        }

        // create QPixmap variables to store the images
        QPixmap *leftView = new QPixmap;
        QPixmap *rightView = new QPixmap;
        // copy the 2 jpegs in buffers
        leftView->loadFromData(&imageData[0], (secondImageStart - 1));
        rightView->loadFromData(&imageData[secondImageStart], (fileLength - secondImageStart));
        // decode jpegs in pointer array
        std::vector<QPixmap> stereoImages(2);
        stereoImages[0] = *leftView;
        stereoImages[1] = *rightView;
        // return pointer array
        vector = stereoImages;
        return true;
    }
    else return false;
}

bool MPO2Mat(QString source, vector<cv::Mat>& vector)
{
    int count = 0;
    int laufIndex, fileLength;
    int secondImageStart = 0;
    // open MPO file as datastream
    QFile imageFile(source);
    // open if exist
    if (imageFile.exists()) {
        // open file in read only mode
        imageFile.open(QIODevice::ReadOnly);
        QDataStream dataInfilestream(&imageFile);
        // get file length
        fileLength = imageFile.size();
        // define data vector
        QVector<uchar> imageData(fileLength);
        // read data from stream
        while(!dataInfilestream.atEnd()) {
            // copy file bytewise
            dataInfilestream >> imageData[count++];
        }
        // close file
        imageFile.close();
        // search for beginning of second image (normaly at half of the full MPO file)
        for (laufIndex = (int)(fileLength * 0.40); laufIndex < (int)(fileLength * 0.60); laufIndex++) {
            if ((imageData[laufIndex] == 0xFF) && (imageData[laufIndex+1] == 0xD8) \
              && (imageData[laufIndex+2] == 0xFF) && (imageData[laufIndex+3] == 0xE1)) {
                secondImageStart = laufIndex;
                break;
            }
        }
        // if no seperator is found
        if (secondImageStart == 0) {
            return false;
        }

        // return buffers : 2 jpegs
        std::vector<cv::Mat> ret(2);
        // copy the 2 jpegs in buffers
        QVector<uchar> leftImageData = imageData.mid(0,secondImageStart - 1);
        QVector<uchar> rightImageData = imageData.mid(secondImageStart,fileLength - secondImageStart);
        // decode jpegs in Mat containers
        ret[0] = imdecode(leftImageData.toStdVector(), CV_LOAD_IMAGE_COLOR);
        ret[1] = imdecode(rightImageData.toStdVector(), CV_LOAD_IMAGE_COLOR);
        // return pointer array
        vector = ret;
        // success
        return true;
    }
    else return false;
}
