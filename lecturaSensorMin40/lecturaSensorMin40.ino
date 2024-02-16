#include <iostream>
#include <SerialStream.h>
int main(){
    using namespace LibSerial;

    SerialStream serial_port;
    serialport.Open("/dev/ttyUSB0"); //Remplazar con el puerto necesario

    serial_port.SetBaudRate(SerialStreamBuf::Baud_P600); //Ajustar al sensor

    if (!Serial_port.good()) { 
        std::cerr << "Error al abrir el puerto serie" << std::endl;
        return 1;
    }

    try {
        while(true) {
            float data[6];
            serial_port.read(reinterpret_cast<char*>(data), sizeof(data));

            for (i = 0; i < 6; ++i){
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
            usleep(1000000);
        }
    }
    catch (const std::exeption& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        serial_port.Close();
        return 1;
    }
    seria_port.Close();
    return 0;
}
