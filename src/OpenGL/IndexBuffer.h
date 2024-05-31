#include "Renderer.h"


class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int getCount() const { return count; }

private:
	unsigned int IndexBufferID=0;
	unsigned int count=0;
};