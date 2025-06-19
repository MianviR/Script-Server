#include <cstdint>
#include <string.h>
#include <stdlib.h>

class message
{
	public:
	static const std::uint8_t header_size = 4;
	static const std::uint16_t max_body_size = 512;

	message() {
		body_size_ = 0;
	}

	std::uint16_t size() const {
		return body_size_ + header_size;
	}

	std::uint16_t body_size() const {
		return body_size_;
	}
	
	std::uint16_t max_size() const {
		return max_body_size + header_size;
	}

	void body_set(char* msg) {
		body_size_ = strlen(msg);
		if (body_size_ > max_body_size) 
			body_size_ = max_body_size;
		memcpy(text + header_size, msg, body_size_); 	
	}	
	
	const char* body_get() const {
		return text+header_size;
	}

	char* body_get() {
		return text+header_size;
	}

	private:
	std::uint32_t header_;
	std::uint16_t body_size_;
	char text[max_body_size + header_size + 1] = "";
};
