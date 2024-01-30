#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO {
	public: 
		// ID ref of elements buffer object
		GLuint ID;

		EBO(GLuint* indices, GLsizeiptr size);
		void Bind();
		void Unbind();
		void Delete();
};

#endif