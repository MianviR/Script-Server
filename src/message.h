#include <cstdint>
#include <string.h>
#include <stdlib.h>

class message
{
	public:
	static const std::uint8_t header_size = 4;
	static const std::uint16_t max_body_size = 512;

	message(std::uint32_t header) {
		header_ = header;
		body_size_ = 0;
	}

	std::uint16_t size() const {
		return body_size_ + header_size;
	}
	
	std::uint16_t max_size() const {
		return max_body_size + header_size;
	}

	void set(char* msg) {
		body_size_ = strlen(msg);
		if (body_size_ > max_body_size) 
			body_size_ = max_body_size;
		memcpy(text + header_size, msg, body_size_); 	
	}	
	
	const char* get() {
		return text;
	}

	private:
	std::uint32_t header_;
	std::uint16_t body_size_;
	char text[max_body_size + header_size] = "";
};
