// -*- C++ -*-
/*!
 * @file  PrintTabletInfo.cpp
 * @brief PrintTabletInfo
 * @date $Date$
 *
 * $Id$
 */

#include "PrintTabletInfo.h"

FILE *fp;


// Module specification
// <rtc-template block="module_spec">
static const char* printtabletinfo_spec[] =
  {
    "implementation_id", "PrintTabletInfo",
    "type_name",         "PrintTabletInfo",
    "description",       "PrintTabletInfo",
    "version",           "1.0.0",
    "vendor",            "ogata-lab",
    "category",          "wacom table",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PrintTabletInfo::PrintTabletInfo(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_positionIn("position", m_position),
    m_pressureIn("pressure", m_pressure)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PrintTabletInfo::~PrintTabletInfo()
{
}



RTC::ReturnCode_t PrintTabletInfo::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("position", m_positionIn);
  addInPort("pressure", m_pressureIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PrintTabletInfo::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t PrintTabletInfo::onActivated(RTC::UniqueId ec_id)
{
		fp=fopen("result.txt","w");
	if(fp==NULL){
		printf("file open error");
		return RTC::RTC_ERROR;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PrintTabletInfo::onDeactivated(RTC::UniqueId ec_id)
{
		fclose(fp);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PrintTabletInfo::onExecute(RTC::UniqueId ec_id)
{
		if(m_positionIn.isNew()){
		m_positionIn.read();
//		fprintf(fp,"%f, %f, \n", m_position.data.x, m_position.data.y);

		std::cout << "position is: " << m_position.data.x << ", " << m_position.data.y << std::endl;
	}

	if(m_pressureIn.isNew()){
		m_pressureIn.read();
		std::cout << "pressure is" << m_pressure.data << std::endl;
	}


	fprintf(fp,"%u, %u, %u\n", (unsigned int)m_position.data.x, (unsigned int)m_position.data.y,(unsigned int)m_pressure.data);

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PrintTabletInfo::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PrintTabletInfo::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void PrintTabletInfoInit(RTC::Manager* manager)
  {
    coil::Properties profile(printtabletinfo_spec);
    manager->registerFactory(profile,
                             RTC::Create<PrintTabletInfo>,
                             RTC::Delete<PrintTabletInfo>);
  }
  
};


