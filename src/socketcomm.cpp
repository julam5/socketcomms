#include "socketcomm.hpp"

cSocketComm::cSocketComm()
{
    sockfd = 0, n = 0;
}


cSocketComm::~cSocketComm()
{

}



bool cSocketComm::initConnection()
{
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout<<"\n Error : Could not create socket \n";
        return false;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9001); 

    if(inet_pton(AF_INET, "192.168.42.1", &serv_addr.sin_addr)<=0)
    {
        std::cout<<"\n inet_pton error occured\n";
        return false;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cout<<"\n Error : Connect Failed \n";
        return false;
    } 

    return true;
}




void cSocketComm::readSocket()
{
    // create the buffer with space for the data
    std::vector<char> buffer(MAX_BUF_LENGTH);
    std::string rcv;   
    int bytesReceived = 0;
    do {
        bytesReceived = recv(sockfd, &buffer[0], buffer.size(), 0);
        // append string from buffer.
        if ( bytesReceived == -1 ) { 
            // error 
        } else {
            rcv.append( buffer.cbegin(), buffer.cend() );
        }
    } while ( bytesReceived == MAX_BUF_LENGTH );
    // At this point we have the available data (which may not be a complete
    // application level message). 

    std::cout<<rcv<<std::endl;
}


#if 0
void cSocketComm::sendStartDvr()
{
    std::stringstream headerStream, dataStream;
    std::string dataString, startString;

    dataStream << "{\"droneId\":\"" << 12155643 << "\",\"action\":\"start\",\"message\":\"start\"}";
    dataString = dataStream.str();

    Reverse32(dataString.length());

    headerStream << jsonSignatureByte1 << jsonSignatureByte2;
    headerStream << dataLenghtByte1 
                 << dataLenghtByte2
                 << dataLenghtByte3
                 << dataLenghtByte4;  //length of data being sent [4 bytes]
    
    //sstd::cout<<buffer,"%c%c%c%c%c%c{\"droneId\":\"777\",\"action\":\"start\",\"message\":\"start\"}",232,7,0x34,0,0,0);

    startString = headerStream.str() + dataString;
    write(sockfd, startString.c_str(), startString.length()); 
}



void cSocketComm::sendStopDvr()
{

    std::stringstream headerStream, dataStream;
    std::string dataString, stopString;

    dataStream << "{\"droneId\":\"" << 12155643 << "\",\"action\":\"stop\",\"message\":\"dronelanded\"}";
    dataString = dataStream.str();

    Reverse32(dataString.length());

    headerStream << jsonSignatureByte1 << jsonSignatureByte2;
    headerStream << dataLenghtByte1 
                 << dataLenghtByte2
                 << dataLenghtByte3
                 << dataLenghtByte4;  //length of data being sent [4 bytes]

    stopString = headerStream.str() + dataString;
    write(sockfd, stopString.c_str(), stopString.length()); 

}
#endif