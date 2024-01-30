#include "VAO.h"

// constuctor that generates a VAO ID
VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

// links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// bind the VAO
void VAO::Bind() {
	glBindVertexArray(ID);
}

// unbind the VAO
void VAO::Unbind() {
	glBindVertexArray(0);
}

// delete the VAO
void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}