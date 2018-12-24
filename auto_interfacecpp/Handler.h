#ifndef _BASESMOOTHINGALGORITHM_H_
#define _BASESMOOTHINGALGORITHM_H_

#include "lcm/lcm.h"
#include "lcm/lcm-cpp.hpp"

#include "lcm1/PacketGPS.hpp"
#include "lcm1/V2X/V2XCommItf/OtherVehicleData.hpp"
#include "lcm1/V2X/V2XCommItf/PacketOtherVehicleData_list.hpp"
#include "Packet.h"
#include <unistd.h>



class Handler
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
   /* std::cout << "-------------- handlerpart3 --------------" << std::endl;
    std::cout << "Received message on channel "<<chan.c_str()<< "Sending index "<<msg->index
   << std::endl;
    std::cout << "-------------- handlerpart4 --------------" << std::endl;
    int i;
    for(i=49;i+1>0;i--){
      std::cout <<  "Sending iby "<<msg->iby[i]<< std::endl;
    }
    int j;
    for(j=2999;j+1>0;j--){
      std::cout <<  "Sending ibcontoury----- "<<j<<"-----"<<msg->ibcontoury[j]<< std::endl;
    }*/
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

	void handleCANMsgMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketCanMsg* msg);
	/*{
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

     // greeter.SayHelloh(ctrldataCANMsg.steer,ctrldataCANMsg.speed);
    // std::cout << "Received message on speedaaaa "<<ctrldataCANMsg.speed<< std::endl;
     
	}*/
  
   PacketCanMsg ctrldataCANMsg;
  void handleIbeoVecMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const PacketIbeoVector* msg);
	/*{
    
    // std::cout <<  "Sending lengthOfObject----- "<<"-----"<<msg->lengthOfObject<< std::endl;
     //int16_t s=msg->lengthOfObject-1;
     //std::cout <<  "Sending lengthOfObject----- "<<"-----"<<msg->ibcontourx.data()<< std::endl;
     // std::cout << "handleIbeoVecMessage Received message on channel "<<chan.c_str()<< std::endl;
     lk.lock();
     memcpy(&ctrldatabeoVec, msg, sizeof(PacketIbeoVector));
     
     lk.unlock();
		 loseCNT = 0;
     // GreeterClient greeter(grpc::CreateChannel(
     // "localhost:50051", grpc::InsecureChannelCredentials()));
     //greeter.SayHelloq(msg->index,msg->lengthOfContour,ctrldatabeoVec.ibcontourx,ctrldatabeoVec.ibcontoury);
     // greeter.SayHelloq();
     //int n;
    // GreeterClient::SayHelloq();
    / n=msg->lengthOfObject;
    
    // for(int i=0;i<n;i++){
    //  std::cout <<  "ctrldatabeoVec.ibcontourx----- "<<i<<msg->ibcontourx.at(i)<< std::endl;
     //  std::cout <<  "ctrldatabeoVec.ibvx----- "<<i<<msg->ibvx.at(i)<< std::endl;
    //   std::cout <<  "ctrldatabeoVec.ibvy----- "<<i<<msg->ibvy.at(i)<< std::endl;
     //  }
     
	}*/
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
  private:
	
	std::mutex lk;
  
};


#endif