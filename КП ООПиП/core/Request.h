#pragma once

#include <memory>

class Request
{
private:
	unsigned int client_id_;
	unsigned int property_id_;
	unsigned int realtor_id_;
public:
	Request() : client_id_(0), property_id_(0), realtor_id_(0){}
	Request(unsigned int client_id, unsigned int property_id, unsigned int realtor_id)
		: client_id_(client_id), property_id_(property_id), realtor_id_(realtor_id){}

	unsigned int client_id() const { return client_id_; }
	unsigned int property_id() const { return property_id_; }
	unsigned int realtor_id() const { return realtor_id_; }

	void set_client_id(unsigned int client_id) { client_id_ = client_id; }
	void set_property_id(unsigned int property_id) { property_id_ = property_id; }
	void set_realtor_id(unsigned int realtor_id) { realtor_id_ = realtor_id; }

    void serialize(std::ofstream& ofs) const {
        ofs.write(reinterpret_cast<const char*>(&client_id_), sizeof(client_id_));
        ofs.write(reinterpret_cast<const char*>(&property_id_), sizeof(property_id_));
        ofs.write(reinterpret_cast<const char*>(&realtor_id_), sizeof(realtor_id_));
    }
    void deserialize(std::ifstream& ifs) {
        ifs.read(reinterpret_cast<char*>(&client_id_), sizeof(client_id_));
        ifs.read(reinterpret_cast<char*>(&property_id_), sizeof(property_id_));
        ifs.read(reinterpret_cast<char*>(&realtor_id_), sizeof(realtor_id_));
    }

	friend bool operator==(const Request& r1, const Request& r2)
	{
		return
			r1.client_id_ == r2.client_id_ &&
			r1.property_id_ == r2.property_id_ &&
			r1.realtor_id_ == r2.realtor_id_;
	}
};

using RequestPtr = std::shared_ptr<Request>;