#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
namespace ggEngine{
	
	class ISerializable{
	protected:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {}
	/*	void serialize(boost::archive::text_oarchive & ar, const unsigned int version){}
		void serialize(boost::archive::text_iarchive & ar, const unsigned int version) {}*/
	};
}
