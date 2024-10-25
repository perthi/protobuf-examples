// -*- mode: c++ -*-
#ifndef KFPBSUBMESSAGESEMLINEARUNITCONVERSION_H
#define KFPBSUBMESSAGESEMLINEARUNITCONVERSION_H
/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/



#include    "KFPBMessageSEM.h"


struct  KFSensorUnitConversion;

class  KFPBSubMessageSEMLinearUnitConversion : public KFPBMessageSEM< SEMLinearUnitConversion >
{
	public:
		API     KFPBSubMessageSEMLinearUnitConversion();
		virtual API  ~KFPBSubMessageSEMLinearUnitConversion();
		virtual void   API  Reset(   SEMLinearUnitConversion *t)  override;
		virtual void   API Reset(  )  override;

		void    API   SetInputType( const eSENSOR_INPUT_TYPE  type );
		void    API   SetMinInput(const float val);
		void    API   SetMaxInput(const float val);
		void    API   SetMaxOutput(const float val);
		void    API   SetMinOutput(const float val);

		eSENSOR_INPUT_TYPE 	   API     GetInputType() const;

		float   API   GetMinInput() const;
		float   API   GetMaxInput() const;
		float   API   GetMinOutput() const;
		float   API   GetMaxOutput() const;

#if defined( __unix__ )  || defined (_WIN32 )
//		void    API SetConfiguration( std::shared_ptr<KFSensorUnitConversion> config );
		void    API SetConfiguration( const  KFSensorUnitConversion * const config );
		virtual string     API str() const override;
		static  string     API  str( KFPBSubMessageSEMLinearUnitConversion *t );
#endif

};

#endif
