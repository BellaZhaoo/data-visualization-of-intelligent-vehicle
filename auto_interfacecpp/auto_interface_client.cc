#include <iostream>
#include<fstream>
#include <memory>
#include <string>
#include <thread>
#include <stdio.h>
#include <atomic>
#include <grpc++/grpc++.h>

#include "lcm/lcm.h"
#include "lcm/lcm-cpp.hpp"

#include"Handler.h"

#include "lcm1/PacketGPS.hpp"
#include "lcm1/V2X/V2XCommItf/OtherVehicleData.hpp"
#include "lcm1/V2X/V2XCommItf/PacketOtherVehicleData_list.hpp"
#include "Packet.h"
#include <unistd.h>

#ifdef BAZEL_BUILD
#include "examples/protos/auto_interface.grpc.pb.h"
#else
#include "auto_interface.grpc.pb.h"
#endif
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using autointerface::HelloRequest;

using autointerface::aPacketReckon;
using autointerface::aPacketCanMsg;

using autointerface::aPacketIbeoVector;

using autointerface::aOtherVehicleData;
using autointerface::aPacketOtherVehicleDatalist;

using autointerface::AutoInterface;
using namespace std;

//using lcm::LCM;
//using lcm::ReceiveBuffer;

HelloRequest MakeHelloRequest(int lengthofplan,float lanelx,
                        float lanely,float stoplanedis,float pathpoints,float pathpointx) {
  HelloRequest n;
  n.set_lengthofplan(lengthofplan);
  n.set_lanelx(lanelx);
  n.set_lanely(lanely);
  n.set_stoplanedis(stoplanedis);
  n.set_pathpoints(pathpoints);
  n.set_pathpointx(pathpointx);
 
  return n;
}
aPacketReckon MakePacketReckon(float dX,float dY,float dThe) {
  aPacketReckon n;
  
  n.set_dx(dX);
  n.set_dy(dY);
  n.set_dthe(dThe);
  
  return n;
}

aPacketCanMsg MakePacketCanMsg1(float steer,float speed,int8_t gearPos,int32_t EPB_status,
int32_t EHB_Pressure,float dX,float dY,float dThe) {
  aPacketCanMsg n;
  
  n.set_steer(steer);
  n.set_speed(speed);
  n.set_gearpos(gearPos);
  n.set_epb_status(EPB_status);
  n.set_ehb_pressure(EHB_Pressure);
  //n.set_sonicx(sonicx);
  //n.set_sonicy(sonicy);
  //n.set_rawdis(rawdis);
  n.mutable_reckon()->CopyFrom(MakePacketReckon(dX,dY,dThe));

  return n;
}

aPacketCanMsg MakePacketCanMsg2(float sonicx,float sonicy) {
  aPacketCanMsg n;
  
  //n.set_steer(steer);
  //n.set_speed(speed);
  //n.set_gearpos(gearPos);
  //n.set_epb_status(EPB_status);
  //n.set_ehb_pressure(EHB_Pressure);
  n.set_sonicx(sonicx);
  n.set_sonicy(sonicy);
  //n.set_rawdis(rawdis);
  //n.mutable_reckon()->CopyFrom(MakePacketReckon(dX,dY,dThe));

  return n;
}

aPacketCanMsg MakePacketCanMsg3(int32_t rawdis) {
  aPacketCanMsg n;
  
  //n.set_steer(steer);
  //n.set_speed(speed);
  //n.set_gearpos(gearPos);
  //n.set_epb_status(EPB_status);
  //n.set_ehb_pressure(EHB_Pressure);
  //n.set_sonicx(sonicx);
  //n.set_sonicy(sonicy);
  n.set_rawdis(rawdis);
  //n.mutable_reckon()->CopyFrom(MakePacketReckon(dX,dY,dThe));

  return n;
}


aPacketIbeoVector MakePacketIbeoVector(int8_t index,int16_t lengthOfObject,int16_t lengthOfContour,
float ibx,float iby,float ibw,float ibl,float ibvx,float ibvy,float ibvabx,
float ibvaby,int16_t ibcontournum,vector<float>&ibcontourx,
vector<float>&ibcontoury) {
  aPacketIbeoVector n;

  n.set_index(index);
  n.set_lengthofobject(lengthOfObject); 
  n.set_lengthofcontour(lengthOfContour);
  n.set_ibx(ibx); 
  n.set_iby(iby);
  n.set_ibw(ibw); 
  n.set_ibl(ibl);
  n.set_ibvx(ibvx); 
  n.set_ibvy(ibvy);
  n.set_ibvabx(ibvabx); 
  n.set_ibvaby(ibvaby);
  n.set_ibcontournum(ibcontournum); 
  int i;
  for(i=0;i<lengthOfContour;i++){
    n.add_ibcontourx(ibcontourx.at(i));
    n.add_ibcontoury(ibcontoury.at(i)); 
  }
 // n.add_ibcontourx(ibcontourx);
 // n.add_ibcontoury(ibcontoury); 

  return n;
}
aOtherVehicleData MakeOtherVehicleData(int32_t stationID,float accuracy, double lat,double lon,double heading,
float speed,double referenceTime,double longitudinalAcceleration, double lateralAcceleration,int32_t platoonID,int32_t posInPlatoon){
  aOtherVehicleData n;

  n.set_stationid(stationID);
  n.set_accuracy(accuracy); 
  n.set_lat(lat);
  n.set_lon(lon); 
  n.set_heading(heading);
  n.set_speed(speed); 
  n.set_referencetime(referenceTime);
  n.set_longitudinalacceleration(longitudinalAcceleration); 
  n.set_lateralacceleration(lateralAcceleration);
  n.set_platoonid(platoonID); 
  n.set_posinplatoon(posInPlatoon);
  return n;
  
}

aPacketOtherVehicleDatalist MakePacketOtherVehicleDatalist(int16_t numOfVehicles,int32_t stationID,float accuracy, double lat,double lon,double heading,
float speed,double referenceTime,double longitudinalAcceleration, double lateralAcceleration,int32_t platoonID,int32_t posInPlatoon){
  aPacketOtherVehicleDatalist n;
 // aOtherVehicleData* m;
  n.set_numofvehicles(numOfVehicles);
 // int i;
 // for(i=0;i<3;i++){
    
 // }
 // m=n.add_
  //m->set_stationid(stationID);
  //m->set_accuracy(accuracy);
 // m->set_lat(lat);
 // m->set_lon(lon); 
 // m->set_heading(heading);
 // m->set_speed(speed); 
  //m->set_referencetime(referenceTime);
  //m->set_longitudinalacceleration(longitudinalAcceleration); 
  //m->set_lateralacceleration(lateralAcceleration);
  //m->set_platoonid(platoonID); 
 // m->set_posinplatoon(posInPlatoon);
  
  
  n.mutable_vehicle()->CopyFrom(MakeOtherVehicleData(stationID,accuracy, lat,lon,heading,
 speed, referenceTime, longitudinalAcceleration,  lateralAcceleration, platoonID, posInPlatoon));

 return n;

}





 // GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
class Handler;
Handler handlerObject;
/*void Handler::handleCANMsgMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketCanMsg* msg){
  std::cout << "handleCANMsgMessage Received message on channel "<<chan.c_str()<< std::endl;
  lk.lock();
     memcpy(&ctrldataCANMsg, msg, sizeof(PacketCanMsg));
     lk.unlock();
		 loseCNT = 0;

  
}
void Handler::handleIbeoVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeoVector* msg){

     lk.lock();
     memcpy(&ctrldatabeoVec, msg, sizeof(PacketIbeoVector));
     
     lk.unlock();
		 loseCNT = 0;

  
}*/

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(AutoInterface::NewStub(channel)) {}

  
////////////////////////////////////////////////////////////////////////////////////////////////////
 void SayHello() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<HelloRequest, HelloRequest> > stream(
        stub_->SayHello(&context));

    std::thread writer([stream]() {
      std::vector<HelloRequest> notes{
        MakeHelloRequest(1,1,1,1.0,1, 2),
        MakeHelloRequest(1,1,1,2.0,1, 3),
        MakeHelloRequest(1,1,1,3.0,1, 4),
        MakeHelloRequest(1,1,1,4.0,1, 5)};
      for (const HelloRequest& note : notes) {
       // std::cout << "Sending message " << note.lengthofplan()<< note.lanelx()<< note.lanely()<< note.stoplanedis()
              //    << note.pathpoints()<< note.pathpointx()  << std::endl;
        stream->Write(note);
      }
      for (const HelloRequest& noteagain : notes) {
       // std::cout << "Sending message " << noteagain.lengthofplan()<< noteagain.lanelx()<< noteagain.lanely()
               //   << noteagain.pathpoints()<< noteagain.pathpointx()  << std::endl;
        stream->Write(noteagain);
      }
      stream->WritesDone();
    });


    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHello rpc failed." << std::endl;
    }
  }

void SayHellog() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<aPacketReckon, aPacketReckon> > stream(
        stub_->SayHellog(&context));

    std::thread writer([stream]() {
      std::vector<aPacketReckon> notes{
        MakePacketReckon(1,2,1),
        MakePacketReckon(1,3,1),
        MakePacketReckon(1,4,1),
        MakePacketReckon(1,5,1)};
      for (const aPacketReckon& note : notes){
       // std::cout << "Sending message PacketReckon:" << note.dx()<< note.dy()<< note.dthe()<< std::endl;
        stream->Write(note);
      }
      stream->WritesDone();
    });

   
//////////////////////////////////////////////////////////////////////////
    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHellog rpc failed." << std::endl;
    }
  }
////////////////////////mark
 void SayHelloh() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<aPacketCanMsg, aPacketCanMsg> > stream(
        stub_->SayHelloh(&context));
    
    // auto f=[steer]()->float{return steer;};
    std::thread writer([stream](){    
    //Handler notea;
    //Handler& noteas=notea;
     // Handler ctrl;
      
       // f();
       // auto l=[](float speed)->float{return speed;};
       // l(speed);
      //float steer1=0;
      //////////////////////
     
     std::vector<aPacketCanMsg> note2s{
       
      
       // MakePacketCanMsg1(handlerObject.ctrldataCANMsg.steer,handlerObject.ctrldataCANMsg.speed,0,0,0,0,0,0)
          MakePacketCanMsg1(handlerObject.ctrldataCANMsg.steer,handlerObject.ctrldataCANMsg.speed,0,0,0,0,0,0)
      // MakePacketCanMsg1(handlerObject.ctrldataCANMsg.steer,handlerObject.ctrldataCANMsg.speed,0,0,handlerObject.ctrldataCANMsg.EHB_Pressure,0,0,0)
        };
      for (const aPacketCanMsg& note2 : note2s){
       // std::cout << "SayHelloh Sending message PacketCanMsg:"<<"steer"<<note2.steer()<<"speed"<<note2.speed()<< std::endl;
        
        stream->Write(note2);
      }
      stream->WritesDone();
    });
    ///////////////////////////////////////////////////////////////////////

    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHelloh rpc failed." << std::endl;
    }
  }

  

void SayHelloq() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<aPacketIbeoVector, aPacketIbeoVector> > stream(
        stub_->SayHelloq(&context));

    std::thread writer([stream](){
     // int m=handlerObject.ctrldatabeoVec.lengthOfContour;
     // for(int i=0;i<m;i++){
       //Handler ctrl;
      
      
        std::vector<aPacketIbeoVector> notes{
       
      /*  MakePacketIbeoVector(handlerObject.ctrldatabeoVec.index,handlerObject.ctrldatabeoVec.lengthOfObject,
        handlerObject.ctrldatabeoVec.lengthOfContour,1,1
        ,3,4,5,6,7,8,1,handlerObject.ctrldatabeoVec.ibcontourx,handlerObject.ctrldatabeoVec.ibcontoury)*/
        /*MakePacketIbeoVector(handlerObject.ctrldatabeoVec.index,1,
        handlerObject.ctrldatabeoVec.lengthOfContour,1,1
        ,3,4,5,6,7,8,1,handlerObject.ctrldatabeoVec.ibcontourx,handlerObject.ctrldatabeoVec.ibcontoury)*/
        MakePacketIbeoVector(handlerObject.ctrldatabeoVec.index,1,
        handlerObject.ctrldatabeoVec.lengthOfContour,1,1
        ,3,4,5,6,7,8,1,handlerObject.ctrldatabeoVec.ibcontourx,handlerObject.ctrldatabeoVec.ibcontoury)};
//,handlerObject.ctrldatabeoVec.ibcontourx.at(i),handlerObject.ctrldatabeoVec.ibcontoury.at(i)
      for (const aPacketIbeoVector& note : notes){
        /*std::cout << "Sending message PacketIbeoVector:" << note.index()<< note.lengthofobject()
        << note.lengthofcontour()<< note.ibx()
        << note.iby()<< note.ibw()<< note.ibl()<< note.ibvx()
        << note.ibvy()<< note.ibvabx()<< note.ibvaby()<< note.ibcontournum()
        << note.ibcontourx()<< note.ibcontoury()<< std::endl;*/
       // std::cout<<"Sending message PacketIbeoVector:" <<note.ibcontourx().data()<<std::endl;
        stream->Write(note);
      }
      // }
      stream->WritesDone();
    });

    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHelloq rpc failed." << std::endl;
    }
  }

  void SayHelloPacketOtherVehicleDatalist() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<aPacketOtherVehicleDatalist, aPacketOtherVehicleDatalist> > stream(
        stub_->SayHelloPacketOtherVehicleDatalist(&context));

    std::thread writer([stream](){
      //int m=handlerObject.ctrldatabeoVec.lengthOfContour;
     // for(int i=0;i<m;i++){
        std::vector<aPacketOtherVehicleDatalist> notes{
       
        MakePacketOtherVehicleDatalist(1,1,1,1,1,1,11,1,1,1,1,1)};
//,handlerObject.ctrldatabeoVec.ibcontourx.at(i),handlerObject.ctrldatabeoVec.ibcontoury.at(i)
      for (const aPacketOtherVehicleDatalist& note : notes){
        /*std::cout << "Sending message PacketIbeoVector:" << note.index()<< note.lengthofobject()
        << note.lengthofcontour()<< note.ibx()
        << note.iby()<< note.ibw()<< note.ibl()<< note.ibvx()
        << note.ibvy()<< note.ibvabx()<< note.ibvaby()<< note.ibcontournum()
        << note.ibcontourx()<< note.ibcontoury()<< std::endl;*/
       // std::cout<<"Sending message PacketOtherVehicleData_list:" << <<std::endl;
      // handlerObject.ctrldataOtherVehicle.vehicle
       
        stream->Write(note);
      }
      // }
      stream->WritesDone();
    });

    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHelloPacketOtherVehicleData_list rpc failed." << std::endl;
    }
  }

  void SayHelloOtherVehicleData() {
    ClientContext context;

    std::shared_ptr<ClientReaderWriter<aOtherVehicleData, aOtherVehicleData> > stream(
        stub_->SayHelloOtherVehicleData(&context));

    std::thread writer([stream](){
      //int m=handlerObject.ctrldatabeoVec.lengthOfContour;
     // for(int i=0;i<m;i++){
        std::vector<aOtherVehicleData> notes{
       
        MakeOtherVehicleData(1,1,1,1,1,1,1,1,1,1,1)};
//,handlerObject.ctrldatabeoVec.ibcontourx.at(i),handlerObject.ctrldatabeoVec.ibcontoury.at(i)
      for (const aOtherVehicleData& note : notes){
        /*std::cout << "Sending message PacketIbeoVector:" << note.index()<< note.lengthofobject()
        << note.lengthofcontour()<< note.ibx()
        << note.iby()<< note.ibw()<< note.ibl()<< note.ibvx()
        << note.ibvy()<< note.ibvabx()<< note.ibvaby()<< note.ibcontournum()
        << note.ibcontourx()<< note.ibcontoury()<< std::endl;*/
       // std::cout<<"Sending message PacketOtherVehicleData_list:" << <<std::endl;
       
        stream->Write(note);
      }
      // }
      stream->WritesDone();
    });

    writer.join();
    Status status = stream->Finish();
    if (!status.ok()) {
      std::cout << "SayHelloPacketOtherVehicleData rpc failed." << std::endl;
    }
  }


 private:
  std::unique_ptr<AutoInterface::Stub> stub_;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
GreeterClient greeter(grpc::CreateChannel( "localhost:50051", grpc::InsecureChannelCredentials()));

void Handler::handleCANMsgMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketCanMsg* msg){
 
   std::cout << "handleCANMsgMessage Received message on channel "<<chan.c_str()<< std::endl;
  lk.lock();
     memcpy(&ctrldataCANMsg, msg, sizeof(PacketCanMsg));
     lk.unlock();
		 loseCNT = 0;
 // greeter.SayHelloh();
}
void Handler::handleIbeoVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeoVector* msg){
     std::cout << "handleIbeoVecMessage Received message on channel "<<chan.c_str()<< std::endl;
     lk.lock();
     memcpy(&ctrldatabeoVec, msg, sizeof(PacketIbeoVector));
     
     lk.unlock();
		 loseCNT = 0;
  greeter.SayHelloh();

  greeter.SayHelloq();
}
/*class Handler
{
public:

	~Handler() {}
  
  
  std::atomic<int> loseCNT{ 1 };
  
	void handleGPSMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketGPS* msg)
	{
    
    //std::cout << "-------------- handlerpart1 --------------" << std::endl;
    //std::cout << "Received message on channel "<<chan.c_str()<< std::endl;
    //std::cout << "Received message on accuracy "<<msg->accuracy<< std::endl;
   // std::cout << "-------------- handlerpart2 --------------" << std::endl;
    lk.lock();
    memcpy(&ctrldata, msg, sizeof(PacketGPS));
    lk.unlock();
		 loseCNT = 0;
      //greeterhand
	}
  
  PacketGPS ctrldata;
  void handleIbeoMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeo* msg)
	{
   
    //std::cout << "Received message on steer "<<msg->ibcontourx<< std::endl; 
    //std::cout << "-------------- handlerparta --------------" << std::endl;
    //std::cout << "Received message on channel "<<chan.c_str()<< std::endl;
   // std::cout << "-------------- handlerpartb --------------" << std::endl;
   // std::cout <<  "Sending ibcontoury----- "<<"-----"<<msg->ibcontoury[20]<< std::endl;
    lk.lock();
    memcpy(&ctrldat, msg, sizeof(PacketIbeo));
    lk.unlock();
		loseCNT = 0;
	}
  PacketIbeo ctrldat;

	void handleCANMsgMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketCanMsg* msg)
	{
     //std::cout << "Received message on steer "<<msg->steer<< std::endl;
     //std::cout << "Received message on speed "<<msg->speed<< std::endl;
     //std::cout << "Received message on EHB_Pressure "<<msg->EHB_Pressure<< std::endl;
    // std::cout << "Received message on reckon.dThe "<<msg->reckon.dThe<< std::endl;
     //std::cout << "Received message on sonicx[5] "<<msg->sonicx<< std::endl;
     //std::cout << "-------------- handlerpartm --------------" << std::endl;
    //std::cout << "handleCANMsgMessage Received message on channel "<<chan.c_str()<< std::endl;
   // std::cout << "-------------- handlerpartn --------------" << std::endl;
     lk.lock();
     memcpy(&ctrldataCANMsg, msg, sizeof(PacketCanMsg));
     lk.unlock();
		 loseCNT = 0;
     //GreeterClient notea;
     //GreeterClient& noteas=notea;

      greeter.SayHelloh(ctrldataCANMsg.steer,ctrldataCANMsg.speed);
    // std::cout << "Received message on speedaaaa "<<ctrldataCANMsg.speed<< std::endl;
     
	}
  
  PacketCanMsg ctrldataCANMsg;
  void handleIbeoVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeoVector* msg)
	{
    
    // std::cout <<  "Sending lengthOfObject----- "<<"-----"<<msg->lengthOfObject<< std::endl;
     //int16_t s=msg->lengthOfObject-1;
     //std::cout <<  "Sending lengthOfObject----- "<<"-----"<<msg->ibcontourx.data()<< std::endl;
     // std::cout << "handleIbeoVecMessage Received message on channel "<<chan.c_str()<< std::endl;
     lk.lock();
     memcpy(&ctrldatabeoVec, msg, sizeof(PacketIbeoVector));
     //memccpy(&ctrlibcontourx,msg->ibcontourx,sizeof(msg->lengthOfContour));
     lk.unlock();
		 loseCNT = 0;
     // GreeterClient greeter(grpc::CreateChannel(
     // "localhost:50051", grpc::InsecureChannelCredentials()));
     greeter.SayHelloq(msg->index,msg->lengthOfContour,ctrldatabeoVec.ibcontourx,ctrldatabeoVec.ibcontoury);
     // greeter.SayHelloq();
     //int n;
    // GreeterClient::SayHelloq();
    // n=msg->lengthOfObject;
    
    // for(int i=0;i<n;i++){
    //  std::cout <<  "ctrldatabeoVec.ibcontourx----- "<<i<<msg->ibcontourx.at(i)<< std::endl;
     //  std::cout <<  "ctrldatabeoVec.ibvx----- "<<i<<msg->ibvx.at(i)<< std::endl;
    //   std::cout <<  "ctrldatabeoVec.ibvy----- "<<i<<msg->ibvy.at(i)<< std::endl;
     //  }
     
	}
  PacketIbeoVector ctrldatabeoVec;
  //PacketIbeoVector ctrlibcontourx;
  void handleSlamPosMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketSlamPos* msg)
	{
     //std::cout <<  "handleSlamPosMessage----- "<<"-----"<<msg->heading<< std::endl;
     //std::cout <<  "handleSlamPosMessage----- "<<"-----"<<msg->accuracy<< std::endl;
    // std::cout <<  "handleSlamPosMessage----- "<<"-----"<<sizeof(PacketSlamPos)<< std::endl;
     
     
     lk.lock();
     memcpy(&ctrldataSlamPos, msg, sizeof(PacketSlamPos));
     lk.unlock();
		 loseCNT = 0;  
     
	}
  PacketSlamPos ctrldataSlamPos;

  void handleSlamMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketSlam* msg)
	{
     //std::cout <<  "handleSlamPosMessage----- "<<"-----"<<msg->heading<< std::endl;
     //std::cout <<  "handleSlamPosMessage----- "<<"-----"<<msg->accuracy<< std::endl;
    // std::cout <<  "handleSlamPosMessage----- "<<"-----"<<sizeof(PacketSlamPos)<< std::endl;
     
     //std::cout <<  "handleSlamMessage----- "<<"-----"<<msg->lane1x[1]<< std::endl;
     lk.lock();
     memcpy(&ctrldataSlam, msg, sizeof(PacketSlam));
     lk.unlock();
		 loseCNT = 0;  
	}
  PacketSlam ctrldataSlam;

  	void handleOtherVehicleDataListMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const V2XCommItf::PacketOtherVehicleData_list* msg)
	{
   // std::cout << "PacketOtherVehicleDatalist "<<chan.c_str()<< std::endl;
   
    //std::cout <<  "handleSlamMessage----- "<<"-----"<<msg->numOfVehicles<< std::endl;
    //std::cout <<  "handleSlamMessage----- "<<"-----"<<msg->vehicle.data()<< std::endl;
    
     lk.lock();
     memcpy(&ctrldataOtherVehicle, msg, sizeof(V2XCommItf::PacketOtherVehicleData_list));
     lk.unlock();
		 loseCNT = 0;
	}
  V2XCommItf::PacketOtherVehicleData_list ctrldataOtherVehicle;
  void handleOtherVehicleDataMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const V2XCommItf::OtherVehicleData* msg)
	{
    //std::cout << "PacketOtherVehicleData "<<chan.c_str()<< std::endl;
   
    //std::cout <<  "handleSlamMessage----- "<<"-----"<<msg->heading<< std::endl;
     lk.lock();
     memcpy(&ctrlOtherVehicle, msg, sizeof(V2XCommItf::OtherVehicleData));
     lk.unlock();
		 loseCNT = 0;
	}
  V2XCommItf::OtherVehicleData ctrlOtherVehicle;
/*
	void handleSlamPosMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketSlamPos* msg)
	{
	}

	void handleGPSPathMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketGPSPATH* msg)
	{
	}

	void handleVELDMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketVELD* msg)
	{
	}

	// 	void handleRoadCamMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketRoad* msg)
	// 	{
	// 	}

	void handleStoplineCamMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketStopLine* msg)
	{
	}

	void handleIbeoVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeoVector* msg)
	{
	}

	void handleRadarMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketRadar* msg)
	{
	}

	void handleMobileyeMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketMobileEye* msg)
	{
	}

	void handleMobileyeVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketMobileEyeVector* msg)
	{
	}

	void handleHADMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketHighResolutionMap* msg)
	{
	}

	void handlePlanMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketPlan* msg)
	{
	}

	void handleOtherVehicleDataListMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const V2XCommItf::PacketOtherVehicleData_list* msg)
	{
	}*/
  /*private:
	
	std::mutex lk;
  
};*/


void* ReceThread(void* arg)
{
	lcm::LCM threadArg = *(lcm::LCM*)arg;
	while (true){
   threadArg.handle();
   //std::cout<<"accuracy"<<handlerObject.ctrldata.accuracy<<std::endl;
  }
  
   
  
		
}
lcm::LCM clcm("udpm://239.255.76.67:7667?ttl=0");
int w=0;
int main(int argc, char** argv) {
//std::cout << "-------------- part1 --------------" << std::endl;

  if (!clcm.good())
		return -1;
	clcm.subscribe("GPS", &Handler::handleGPSMessage, &handlerObject);
  clcm.subscribe("Ibeo", &Handler::handleIbeoMessage, &handlerObject);
  clcm.subscribe("CANMsg", &Handler::handleCANMsgMessage, &handlerObject);
  clcm.subscribe("IbeoVector", &Handler::handleIbeoVecMessage, &handlerObject);
  clcm.subscribe("SlamPos", &Handler::handleSlamPosMessage, &handlerObject);
  clcm.subscribe("Slam", &Handler::handleSlamMessage, &handlerObject);
  clcm.subscribe("OtherVehicleData_list", &Handler::handleOtherVehicleDataListMessage, &handlerObject);
  clcm.subscribe("OtherVehicleData", &Handler::handleOtherVehicleDataMessage, &handlerObject);
	/*clcm.subscribe("VELD", &Handler::handleVELDMessage, &handlerObject);
	clcm.subscribe("GPSPath", &Handler::handleGPSPathMessage, &handlerObject);
	// 	clcm.subscribe("Reckon", &Handler::handleReckonMessage, &handlerObject);
	clcm.subscribe("StoplineCam", &Handler::handleStoplineCamMessage, &handlerObject);
	// 	clcm.subscribe("RoadCam", &Handler::handleRoadCamMessage, &handlerObject);
	 
	clcm.subscribe("IbeoVector", &Handler::handleIbeoVecMessage, &handlerObject);
	clcm.subscribe("Radar", &Handler::handleRadarMessage, &handlerObject);
	clcm.subscribe("Plan", &Handler::handlePlanMessage, &handlerObject);
	
	clcm.subscribe("MobileEye", &Handler::handleMobileyeMessage, &handlerObject);
	clcm.subscribe("MobileEyeVector", &Handler::handleMobileyeVecMessage, &handlerObject);
	clcm.subscribe("HAD", &Handler::handleHADMessage, &handlerObject);
	clcm.subscribe("SlamPos", &Handler::handleSlamPosMessage, &handlerObject);
	clcm.subscribe("OtherVehicleData_list", &Handler::handleOtherVehicleDataListMessage, &handlerObject);*/
	// 	/*HANDLE HHH = */CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReceThread, (LPVOID*)&clcm, 0, NULL);
	/*std::cout<<handlerObject.ctrldata.accuracy<<handlerObject.ctrldata.heading<<std::endl;
 // std::cout<<"-----------**----------"<<handlerObject.ctrldat.ibcontoury[30000]<<handlerObject.ctrldat.ibvy[50]<<std::endl;
 for(int i=2999;i+1>0;i--){
   std::cout<<"-----------**----------"<<i<<"-----------**----------"<<handlerObject.ctrldat.ibcontoury[i]<<std::endl;
 }*/
  //std::cout<<"steer"<<handlerObject.ctrldataCANMsg.steer<<std::endl;
  //std::cout<<"speed"<<handlerObject.ctrldataCANMsg.speed<<std::endl;
 //std::cout<<"reckon"<<handlerObject.ctrldataCANMsg.reckon.dThe<<std::endl;
  
  //std::cout << "-------------- part2 --------------" << std::endl;
	pthread_t lcmThreadId;
	int ret = pthread_create(&lcmThreadId, NULL, ReceThread, &clcm);
  //std::cout << "-------------- part3 --------------" << std::endl;
  /*PacketGPS packetgps;
  handlerObject.handleGPSMessage(NULL,"GPS",&packetgps);
  PacketIbeo packetibeo;
  handlerObject.handleIbeoMessage(NULL,"Ibeo",&packetibeo);
  PacketCanMsg packetcanmsg;
  handlerObject.handleCANMsgMessage(NULL,"CANMsg",&packetcanmsg);
  */
  //PacketCanMsg packetcanmsg;
  //handlerObject.handleCANMsgMessage(NULL,"CANMsg",&packetcanmsg);
 // PacketGPS packetgps;
  //handlerObject.handleGPSMessage(NULL,"GPS",&packetgps);
  //std::cout << "-------------- part4 --------------" << std::endl;
	
  ////////////////////////////////
 
  //std::cout << "-------------- part5 --------------" << std::endl;
  //Handler greeter(grpc::CreateChannel(
      //"localhost:50051", grpc::InsecureChannelCredentials()));
  GreeterClient greeter(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  
 

  std::cout << "-------------- SayHello --------------" << std::endl;
  greeter.SayHello();
  greeter.SayHellog();
  //greeter.SayHelloh();
 // greeter.SayHelloq();
  greeter.SayHelloPacketOtherVehicleDatalist();
  greeter.SayHelloOtherVehicleData();
 // greeter.SayHelloh();
 
  //greeter.SayHelloq();
 
  
  
int mark1=0;  
while (true)
	{
  //if(mark1%10!=1){
   // greeter.SayHelloh();
  //  }
  //if(mark1%10==1){
   // greeter.SayHelloq();
   // }
 // mark1++;
  // greeter.SayHelloq();
  //greeter.SayHelloh();
  usleep(90000);
	} 
   return 0;
  /////////////////////////////////
 
 
}







///////////////////



