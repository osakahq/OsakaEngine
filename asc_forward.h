 #include "stdafx.h"
#ifndef ASC_FORWARD_H
#define ASC_FORWARD_H
namespace Osaka{
	namespace Asc{
		class AscApplicationCreator; typedef std::shared_ptr<AscApplicationCreator> AscApplicationCreatorPTR;
		class AscApplication;		 typedef std::shared_ptr<AscApplication> AscApplicationPTR;
	}
}
#endif;