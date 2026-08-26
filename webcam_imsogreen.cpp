#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

int main(int arcg, char** arcgv){
    VideoCapture cap;   // Classe para tratar com captura de vídeo em arquivos e dispositivos
    double width, height;
    Mat frame;
    int counter;

    cap.open(0, CAP_DSHOW); // CAP_DSHOW é a especificação de API de backend para video. Pode ser usado para forçar uma implementação de leitura específica.
    if(!cap.isOpened()){
        cerr <<  "Não foi possível abrir a câmera." << endl;
        return -1;
    }
    width = cap.get(CAP_PROP_FRAME_WIDTH); // Duas características do objeto que são as dimensões de 1 frame do vídeo
    height = cap.get(CAP_PROP_FRAME_HEIGHT);
    cout << "Largura: " << width << endl;
    cout << "Altura: " << height << endl;

    Size frameSize(static_cast<int>(width), static_cast<int>(height));  // Classe que define o tamanho de um frame do vídeo. Argumento de VideoWriter

    int type = VideoWriter::fourcc('M', 'J', 'P', 'G');
    double fps = cap.get(CAP_PROP_FPS);
    if (fps <= 0) fps = 30.0;

    string path = "../output.avi";  // Destino dos frames do video
    VideoWriter out (path, type, fps, frameSize, true); // o último argumento define se o vídeo será em cores ou não
    for(counter=0; cap.read(frame); counter++){
        flip(frame, frame, 1);
        for(int i = 0; i < height; i++){
            uchar* ptr = frame.ptr<uchar>(i);
            //int num_elementos = width*frame.channels();
            for(int j = 0;j < width; j++){
                int greeness = 100;
                if(ptr[3*j+1] < (255-greeness)){
                    ptr[3*j+1] += greeness;
                }else{
                    ptr[3*j+1] = 255;
                }
               /*
               // Goner-ed webcam
               int mean = (ptr[3*j] + ptr[3*j+1] + ptr[3*j+2])/3;
               ptr[3*j] = mean; ptr[3*j+1] = mean; ptr[3*j+2] = mean;
               */
            }
        }
        out << frame; // Passa o frame lido para o vídeo de saída(VideoWriter)
        imshow("Frame", frame);
        
        int tecla = waitKey(30);
        if(tecla >= 0) break; // Se alguma tecla foi pressionada, sai do loop

        if(getWindowProperty("Frame", WND_PROP_VISIBLE) < 1) break;
    }
    std::cout << "Numero de frames: " << counter << "\n";

    cap.release(); 
    out.release();
    destroyAllWindows();
    return 0;
}