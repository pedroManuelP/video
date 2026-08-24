#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

int main(int arcg, char** arcgv){
    cv::VideoCapture cap;   // Classe para tratar com captura de vídeo em arquivos e dispositivos
    double width, height;
    cv::Mat frame;
    int counter;

    cap.open(0);
    if(!cap.isOpened()) return -1;

    width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Duas características do objeto que são as dimensões de 1 frame do vídeo
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Largura: " << width << endl;
    cout << "Altura: " << height << endl;

    cv::Size frameSize(static_cast<int>(width), static_cast<int>(height));  // Classe que define o tamanho de um frame do vídeo. Argumento de VideoWriter

    int type = cap.get(cv::CAP_PROP_FOURCC);    // Código(codec) do vídeo, que define o formato de compressão do vídeo. Argumento de VideoWriter

    string path = "../output.avi";  // Destino dos frames do video
    cv::VideoWriter out (path, type, cap.get(cv::CAP_PROP_FPS), frameSize, true); // o último argumento define se o vídeo será em cores ou não
    for(counter=0; cap.read(frame); counter++){
        cv::flip(frame, frame, 1);
        out << frame; // Passa o frame lido para o vídeo de saída(VideoWriter)
        cv::imshow("Frame", frame);
        
        int tecla = cv::waitKey(30);
        if(tecla >= 0) break; // Se alguma tecla foi pressionada, sai do loop

        if(cv::getWindowProperty("Frame", cv::WND_PROP_VISIBLE) < 1) break;
    }
    std::cout << "Numero de frames: " << counter << "\n";

    cap.release(); 
    out.release();
    cv::destroyAllWindows();
    return 0;
}