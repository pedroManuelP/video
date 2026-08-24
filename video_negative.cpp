#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <ctime>

using namespace std;

int main(int arcg, char** arcgv){
    cv::VideoCapture cap;   // Classe para tratar com captura de vídeo em arquivos e dispositivos
    double width, height;
    cv::Mat frame;
    int counter;

    cap.open("../video.mp4");
    if(!cap.isOpened()) return -1;

    width = cap.get(cv::CAP_PROP_FRAME_WIDTH); // Duas características do objeto que são as dimensões de 1 frame do vídeo
    height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    cout << "Largura: " << width << endl;
    cout << "Altura: " << height << endl;

    cv::Size frameSize(static_cast<int>(width), static_cast<int>(height));  // Classe que define o tamanho de um frame do vídeo. Argumento de VideoWriter

    int type = cap.get(cv::CAP_PROP_FOURCC);    // Código(codec) do vídeo, que define o formato de compressão do vídeo. Argumento de VideoWriter

    string path = "../output.avi";  // Destino dos frames do video
    cv::VideoWriter out (path, type, cap.get(cv::CAP_PROP_FPS), frameSize, true); // o último argumento define se o vídeo será em cores ou não
    
    time_t time_now = time(nullptr);
    for(counter=0; cap.read(frame); counter++){
        for(int i = 0;i < height;i++){
            // Pega um ponteiro para a linha inteira (todos os canais B, G, R)
            uchar* ptr = frame.ptr<uchar>(i);
            
            // O número total de elementos nessa linha é colunas * canais (3)
            int total_elementos = frame.cols * frame.channels();
    
            for(int j = 0; j < total_elementos; j++){
                ptr[j] = 255 - ptr[j];
            }
        }
        out << frame; // Passa o frame lido para o vídeo de saída(VideoWriter)
        cv::imshow("Frame", frame);
        
        int tecla = cv::waitKey(30);
        if(tecla >= 0) break; // Se alguma tecla foi pressionada, sai do loop

        if(cv::getWindowProperty("Frame", cv::WND_PROP_VISIBLE) < 1) break;
    }
    std::cout << "Tempo de execução: " << difftime(time(nullptr), time_now) << " segundos\n";
    std::cout << "Numero de frames: " << counter << "\n";

    cap.release(); 
    out.release();
    cv::destroyAllWindows();
    return 0;
}