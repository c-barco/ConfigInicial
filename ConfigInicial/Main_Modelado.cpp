/* Barco Núñez Claudia Citlali
* No. de Cuenta: 422067621
* Fecha: 01-03-2026
* Practica 4. Modelado geométrico
/*/


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4. Claudia Barco", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);


		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint baseColorLoc = glGetUniformLocation(ourShader.Program, "baseColor"); //para cambiar el color 


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);

		//CUERPO

		//costado en z positivo

		//fila inferior
		glUniform3f(baseColorLoc, 0.85f, 0.34f, 0.02f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -1.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -1.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.85f, 0.34f, 0.02f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -1.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, -1.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.85f, 0.34f, 0.02f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, -1.5f, 2.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -1.0f, 2.5f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fila media
		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(2.5f, -0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -0.5f, 2.5f));
		model = glm::scale(model, glm::vec3(4.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fila superior
		glUniform3f(baseColorLoc, 0.85f, 0.34f, 0.02f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.85f, 0.34f, 0.02f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 0.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pecho
		//fila superior
		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 0.5f, 0.5f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fila media
		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -0.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.804f, 0.502f, 0.086f); //#3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.820f, 0.573f, 0.188f); //#5
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -0.5f, -0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//fila inferior
		glUniform3f(baseColorLoc, 0.804f, 0.502f, 0.086f); //#3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -1.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.820f, 0.573f, 0.188f); //#5
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//costado en z negativo

		// fila inferior
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -1.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -1.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, -1.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, -1.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, -1.5f, -1.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, -1.0f, -1.5f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// fila media
		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -0.5f, -1.5f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, -0.5f, -1.5f));
		model = glm::scale(model, glm::vec3(4.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// fila superior
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 0.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//parte trasera
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -0.5f, 0.5f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//lomo

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//PATAS
		//delantera derecha
		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, -2.5f, 2.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.25, -3.5f, 2.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.25, -4.5f, 2.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.278f, 0.173f); //#1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.75, -5.5f, 2.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.75, -5.5f, 2.5f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//delantera izquierda

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, -2.5f, -1.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.25f, -3.5f, -1.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.25f, -4.5f, -1.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.278f, 0.173f); //#1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.75f, -5.5f, -1.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.75f, -5.5f, -1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//trasera derecha
		glUniform3f(baseColorLoc, 0.88f, 0.37f, 0.02f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -2.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5, -2.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5, -3.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5, -4.5f, 2.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.278f, 0.173f); //#1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0, -5.5f, 2.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// trasera izquierda
		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -2.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, -2.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -3.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, -4.5f, -1.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.278f, 0.173f); //#1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f, -5.5f, -1.5f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//CABEZA

		//fila inferior
		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 1.75f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 1.25f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.0f, 1.25f, 2.75f));
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.0f, 2.75f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//bigote derecho

		glUniform3f(baseColorLoc, 0.149f, 0.243f, 0.200f); //#11
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 1.75f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 2.25f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 2.625f, 2.275f));
		model = glm::scale(model, glm::vec3(1.0f, 0.25f, 2.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//filas medias
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 4.0f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 3.0f, 2.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 3.0f, 2.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//ojo derecho
		glUniform3f(baseColorLoc, 0.035f, 0.247f, 0.184f); //#10
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 3.627f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.75f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.416f, 0.675f, 0.176f); //#9
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 3.627f, 1.625f));
		model = glm::scale(model, glm::vec3(1.0f, 1.75f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 4.0f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 4.0f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 5.0f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 5.0f, 2.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 5.0f, 1.625f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//oreja derecha

		glUniform3f(baseColorLoc, 0.478f, 0.251f, 0.129f); //#12
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 6.0f, 3.25f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//boca

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 1.25f, 1.875f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.149f, 0.243f, 0.200f); //#11
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 1.25f, 1.375f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 2.0f, 1.625f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 2.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//parte trasera de la cabeza
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 2.75f, 1.625f));
		model = glm::scale(model, glm::vec3(1.0f, 4.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	
		//lado izquierdo de la cabeza

		// fila inferior
		glUniform3f(baseColorLoc, 0.753f, 0.306f, 0.012f); //#6
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 1.75f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 1.25f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.0f, 1.25f, -1.75f));
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 2.0f, -1.75f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// bigote izquierdo
		glUniform3f(baseColorLoc, 0.149f, 0.243f, 0.200f); //#11
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 1.75f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 2.25f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 2.625f, -1.275f));
		model = glm::scale(model, glm::vec3(1.0f, 0.25f, 2.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// filas medias
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 4.0f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 3.0f, -1.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 3.0f, -1.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ojo izquierdo
		glUniform3f(baseColorLoc, 0.416f, 0.675f, 0.176f); //#9
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 3.627f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.75f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.035f, 0.247f, 0.184f); //#10
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 3.627f, -0.625f));
		model = glm::scale(model, glm::vec3(1.0f, 1.75f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 4.0f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 4.0f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.5f, 5.0f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 5.0f, -1.75f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 5.0f, -0.625f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// oreja izquierda
		glUniform3f(baseColorLoc, 0.478f, 0.251f, 0.129f); //#12
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 6.0f, -2.25f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// boca izquierda
		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 1.25f, -0.875f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.149f, 0.243f, 0.200f); //#11
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 1.25f, -0.375f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 2.0f, -0.625f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 2.0f, 0.0f)); 
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// parte trasera de la cabeza
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 2.75f, -0.625f));
		model = glm::scale(model, glm::vec3(1.0f, 4.5f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		//detalles de simetria

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.5f, 2.75f, 0.5f));
		model = glm::scale(model, glm::vec3(1.0f, 4.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.5f, 4.375f, 0.5f));
		model = glm::scale(model, glm::vec3(1.0f, 2.25f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//nariz
		glUniform3f(baseColorLoc, 0.882f, 0.278f, 0.173f); //#1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 3.125f, 0.5f));
		model = glm::scale(model, glm::vec3(1.875f, 1.25f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glUniform3f(baseColorLoc, 0.149f, 0.243f, 0.200f); //#11
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 2.0f, 0.5f));
		model = glm::scale(model, glm::vec3(1.5f, 1.0f, 0.75f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.972f, 0.745f, 0.380f); //#13
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-4.75f, 1.25f, 0.5f));
		model = glm::scale(model, glm::vec3(1.5f, 0.5f, 1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//detalle orejas
		glUniform3f(baseColorLoc, 0.925f, 0.329f, 0.020f); //#7
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 6.0f, -1.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-3.0f, 5.0f, 1.0f));
		model = glm::scale(model, glm::vec3(2.5f, 1.0f, 4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.925f, 0.329f, 0.020f); //#7
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.5f, 6.0f, 2.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//COLA
		glUniform3f(baseColorLoc, 0.851f, 0.337f, 0.020f); //#4
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.5f, 1.5f, 0.5f));
		model = glm::scale(model, glm::vec3(1.0f, 3.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.5f, 3.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 4.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.882f, 0.373f, 0.020f); //#2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 5.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(baseColorLoc, 0.922f, 0.412f, 0.024f); //#8
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.5f, 6.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }


