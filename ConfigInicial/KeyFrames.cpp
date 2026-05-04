/* Barco Nunez Claudia Citlali
* No. de Cuenta: 422067621
* Fecha: 03-05-2026
* Practica 12. Animacion por Keyframes
/*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#if defined(_WIN32)
#include <direct.h>    // _mkdir en Windows
#else
#include <sys/stat.h>  // mkdir en Linux/Mac
#endif

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"


// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();
void SaveAnimationToFile();      
bool LoadAnimationFromFile(const std::string& filename);  
void EnsureAnimationsFolder();   

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
float bodyTilt = 0.0f;
float bodySpin= 0.0f;
int dogAnim = 0;
float head = 0.0f;
float tail = 0.0f;


float legFL = 0.0f;   // Pata delantera izquierda
float legFR = 0.0f;   // Pata delantera derecha 
float legBL = 0.0f;   // Pata trasera izquierda
float legBR = 0.0f;   // Pata trasera derecha


//KeyFrames
float dogPosX, dogPosY, dogPosZ;

#define MAX_FRAMES 150
int i_max_steps = 200;
int i_curr_steps = 0;

typedef struct _frame {

	float rotDog;
	float rotDogInc;

	float bodyTilt;
	float bodyTiltInc;

	float bodySpin;
	float bodySpinInc;

	float dogPosX;
	float dogPosY;
	float dogPosZ;

	float incX;
	float incY;
	float incZ;

	float head;
	float tail;

	float legFL;
	float legFR;
	float legBL;
	float legBR;

	float headInc;
	float tailInc;
	float legFLInc;
	float legFRInc;
	float legBLInc;
	float legBRInc;

} FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;
bool pendingSave = false;
bool pendingLoad = false;

void saveFrame(void) {
	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;

	KeyFrame[FrameIndex].rotDog = rotDog;
	KeyFrame[FrameIndex].bodyTilt = bodyTilt;
	KeyFrame[FrameIndex].bodySpin = bodySpin;

	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].tail = tail;

	// Guardar cada pata por separado
	KeyFrame[FrameIndex].legFL = legFL;
	KeyFrame[FrameIndex].legFR = legFR;
	KeyFrame[FrameIndex].legBL = legBL;
	KeyFrame[FrameIndex].legBR = legBR;

	FrameIndex++;
}

void resetElements(void)
{
	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;

	rotDog = KeyFrame[0].rotDog;
	bodyTilt = KeyFrame[0].bodyTilt;
	bodySpin = KeyFrame[0].bodySpin;

	head = KeyFrame[0].head;
	tail = KeyFrame[0].tail;

	legFL = KeyFrame[0].legFL;
	legFR = KeyFrame[0].legFR;
	legBL = KeyFrame[0].legBL;
	legBR = KeyFrame[0].legBR;
}

void interpolation(void)
{
	KeyFrame[playIndex].incX =
		(KeyFrame[playIndex + 1].dogPosX - KeyFrame[playIndex].dogPosX) / i_max_steps;

	KeyFrame[playIndex].incY =
		(KeyFrame[playIndex + 1].dogPosY - KeyFrame[playIndex].dogPosY) / i_max_steps;

	KeyFrame[playIndex].incZ =
		(KeyFrame[playIndex + 1].dogPosZ - KeyFrame[playIndex].dogPosZ) / i_max_steps;

	KeyFrame[playIndex].rotDogInc =
		(KeyFrame[playIndex + 1].rotDog - KeyFrame[playIndex].rotDog) / i_max_steps;

	KeyFrame[playIndex].bodyTiltInc =
		(KeyFrame[playIndex + 1].bodyTilt - KeyFrame[playIndex].bodyTilt) / i_max_steps;

	KeyFrame[playIndex].bodySpinInc = (
		(KeyFrame[playIndex + 1].bodySpin - KeyFrame[playIndex].bodySpin) / i_max_steps);

	KeyFrame[playIndex].headInc =
		(KeyFrame[playIndex + 1].head - KeyFrame[playIndex].head) / i_max_steps;

	KeyFrame[playIndex].tailInc =
		(KeyFrame[playIndex + 1].tail - KeyFrame[playIndex].tail) / i_max_steps;

	// Interpolacion independiente para cada pata
	KeyFrame[playIndex].legFLInc =
		(KeyFrame[playIndex + 1].legFL - KeyFrame[playIndex].legFL) / i_max_steps;

	KeyFrame[playIndex].legFRInc =
		(KeyFrame[playIndex + 1].legFR - KeyFrame[playIndex].legFR) / i_max_steps;

	KeyFrame[playIndex].legBLInc =
		(KeyFrame[playIndex + 1].legBL - KeyFrame[playIndex].legBL) / i_max_steps;

	KeyFrame[playIndex].legBRInc =
		(KeyFrame[playIndex + 1].legBR - KeyFrame[playIndex].legBR) / i_max_steps;
}




void EnsureAnimationsFolder()
{
#if defined(_WIN32)
	_mkdir("animations");
#else
	mkdir("animations", 0755);
#endif
}

void SaveAnimationToFile()
{
	if (FrameIndex < 2)
	{
		printf("[GUARDAR] Se necesitan al menos 2 keyframes para guardar.\n");
		return;
	}

	EnsureAnimationsFolder();

	std::string name;
	printf("Nombre del archivo (sin extension): ");
	fflush(stdout);
	std::cin >> name;

	std::string path = "animations/" + name + ".txt";
	std::ofstream file(path);
	if (!file.is_open())
	{
		printf("[ERROR] No se pudo crear el archivo: %s\n", path.c_str());
		return;
	}

	file << "FRAMES " << FrameIndex << "\n";
	for (int i = 0; i < FrameIndex; i++)
	{
		file << "FRAME " << i << "\n";
		file << "dogPosX " << KeyFrame[i].dogPosX << "\n";
		file << "dogPosY " << KeyFrame[i].dogPosY << "\n";
		file << "dogPosZ " << KeyFrame[i].dogPosZ << "\n";
		file << "rotDog " << KeyFrame[i].rotDog << "\n";
		file << "bodyTilt " << KeyFrame[i].bodyTilt << "\n";
		file << "bodySpin " << KeyFrame[i].bodySpin << "\n";
		file << "head " << KeyFrame[i].head << "\n";
		file << "tail " << KeyFrame[i].tail << "\n";
		file << "legFL " << KeyFrame[i].legFL << "\n";
		file << "legFR " << KeyFrame[i].legFR << "\n";
		file << "legBL " << KeyFrame[i].legBL << "\n";
		file << "legBR " << KeyFrame[i].legBR << "\n";
		file << "END_FRAME\n";
	}
	file.close();
	printf("Animacion guardada en: %s  (%d keyframes)\n", path.c_str(), FrameIndex);
}
bool LoadAnimationFromFile(const std::string& filename) {
	std::string path = "animations/" + filename + ".txt";
	std::ifstream file(path);

	if (!file.is_open()) {
		printf("No se pudo abrir el archivo: %s\n", path.c_str());
		return false;
	}

	// 1. Limpiar los KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++) {
		memset(&KeyFrame[i], 0, sizeof(FRAME));  
	}

	std::string line;
	int currentFrameLoading = -1;

	// 2. Lectura 
	while (std::getline(file, line)) {
		
		if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos)
			continue;

		std::stringstream ss(line);
		std::string key;
		ss >> key;

		// Identificadores de estructura
		if (key == "FRAMES") continue;
		if (key == "FRAME") {
			currentFrameLoading++;
			continue;
		}
		if (key == "END_FRAME") continue;

		// Carga de valores numéricos
		float val;
		if (!(ss >> val)) continue;

		if (currentFrameLoading >= 0 && currentFrameLoading < MAX_FRAMES) {
			if (key == "dogPosX")      KeyFrame[currentFrameLoading].dogPosX = val;
			else if (key == "dogPosY")  KeyFrame[currentFrameLoading].dogPosY = val;
			else if (key == "dogPosZ")  KeyFrame[currentFrameLoading].dogPosZ = val;
			else if (key == "rotDog")   KeyFrame[currentFrameLoading].rotDog = val;
			else if (key == "bodyTilt") KeyFrame[currentFrameLoading].bodyTilt = val;
			else if (key == "bodySpin") KeyFrame[currentFrameLoading].bodySpin = val;
			else if (key == "head")     KeyFrame[currentFrameLoading].head = val;
			else if (key == "tail")     KeyFrame[currentFrameLoading].tail = val;
			else if (key == "legFL")    KeyFrame[currentFrameLoading].legFL = val;
			else if (key == "legFR")    KeyFrame[currentFrameLoading].legFR = val;
			else if (key == "legBL")    KeyFrame[currentFrameLoading].legBL = val;
			else if (key == "legBR")    KeyFrame[currentFrameLoading].legBR = val;
		}
	}

	file.close();

	// 3. Actualizar el índice global 
	FrameIndex = currentFrameLoading + 1;

	if (FrameIndex > 0) {
		printf("%d frames cargados.\n", FrameIndex);
		return true;
	}
	else {
		printf("Error en archivo.\n");
		return false;
	}
}

// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{

	EnsureAnimationsFolder();
	{
		char resp;
		printf("Cargar animacion desde archivo? (s/n): ");
		fflush(stdout);
		std::cin >> resp;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (resp == 's' || resp == 'S')
		{
			std::string animName;
			printf("Nombre del archivo (sin extension, carpeta animations/): ");
			fflush(stdout);
			std::cin >> animName;
			if (!LoadAnimationFromFile(animName))
			{
				printf("No se cargo ninguna animacion. Iniciando en blanco.\n");
			}
		}
		else
		{
			printf("Iniciando sin animacion cargada.\n");
		}
	}

	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "P12. Barco Claudia", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");


	//models
	Model DogBody((char*)"Models/dog_animation/DogBody.obj");
	Model HeadDog((char*)"Models/dog_animation/HeadDog.obj");
	Model DogTail((char*)"Models/dog_animation/TailDog.obj");
	Model F_RightLeg((char*)"Models/dog_animation/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/dog_animation/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/dog_animation/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/dog_animation/B_LeftLegDog.obj");
	Model Piso((char*)"Models/piso/piso.obj");
	Model Ball((char*)"Models/ball/ball.obj");


	// Inicializar KeyFrames en cero
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].dogPosX = 0;
		KeyFrame[i].dogPosY = 0;
		KeyFrame[i].dogPosZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotDog = 0;
		KeyFrame[i].rotDogInc = 0;
		KeyFrame[i].bodyTilt = 0;
		KeyFrame[i].bodyTiltInc = 0;
		KeyFrame[i].bodySpin = 0;
		KeyFrame[i].bodySpinInc = 0;
		KeyFrame[i].head = 0;
		KeyFrame[i].tail = 0;
		KeyFrame[i].legFL = 0;
		KeyFrame[i].legFR = 0;
		KeyFrame[i].legBL = 0;
		KeyFrame[i].legBR = 0;
		KeyFrame[i].headInc = 0;
		KeyFrame[i].tailInc = 0;
		KeyFrame[i].legFLInc = 0;
		KeyFrame[i].legFRInc = 0;
		KeyFrame[i].legBLInc = 0;
		KeyFrame[i].legBRInc = 0;
	}


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp


		// Procesar guardado pendiente (fuera del callback)
		if (pendingSave)
		{
			pendingSave = false;
			SaveAnimationToFile();
		}

		// Procesar carga pendiente
		if (pendingLoad)
		{
			pendingLoad = false;
			std::string animName;
			printf("Nombre del archivo a cargar (sin extension): ");
			fflush(stdout);
			std::cin >> animName;
			if (LoadAnimationFromFile(animName))
			{
				play = false;
				playIndex = 0;
				i_curr_steps = 0;
				resetElements();
				printf("Animacion cargada correctamente.\n");
			}
		}

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);


		//Carga de modelo 
		view = camera.GetViewMatrix();

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);


		model = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));
		model = glm::rotate(model, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(bodyTilt), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(bodySpin), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);


		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogTail.Draw(lightingShader);


		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(legFL), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);


		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(legFR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);

		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218));
		model = glm::rotate(model, glm::radians(legBL), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_LeftLeg.Draw(lightingShader);


		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(legBR), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader);


		model = glm::mat4(1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//Ball.Draw(lightingShader);
		glDisable(GL_BLEND);
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls
	if (keys[GLFW_KEY_2]) rotDog += 0.01f;
	if (keys[GLFW_KEY_3]) rotDog -= 0.01f;
	if (keys[GLFW_KEY_4]) bodyTilt += 0.01f;
	if (keys[GLFW_KEY_5]) bodyTilt -= 0.01f;
	if (keys[GLFW_KEY_8]) bodySpin+= 0.01f;
	if (keys[GLFW_KEY_9]) bodySpin -= 0.01f;

	// Cabeza
	if (keys[GLFW_KEY_Q]) head += 0.01f;
	if (keys[GLFW_KEY_E]) head -= 0.01f;

	// Cola
	if (keys[GLFW_KEY_Z]) tail += 0.01f;
	if (keys[GLFW_KEY_X]) tail -= 0.01f;


	// Pata Delantera Izquierda  (F_Left)  -> teclas C / V
	if (keys[GLFW_KEY_C]) legFL += 0.05f;
	if (keys[GLFW_KEY_V]) legFL -= 0.05f;

	// Pata Delantera Derecha    (F_Right) -> teclas F / R 
	if (keys[GLFW_KEY_F]) legFR += 0.05f;
	if (keys[GLFW_KEY_R]) legFR -= 0.05f;

	// Pata Trasera Izquierda    (B_Left)  -> teclas B / N
	if (keys[GLFW_KEY_B]) legBL += 0.05f;
	if (keys[GLFW_KEY_N]) legBL -= 0.05f;
	// Pata Trasera Derecha      (B_Right) -> teclas M / (,)
	if (keys[GLFW_KEY_M])           legBR += 0.05f;
	if (keys[GLFW_KEY_COMMA])       legBR -= 0.05f;

	// Movimiento del perro en el mundo
	if (keys[GLFW_KEY_H]) dogPosZ += 0.0001f;
	if (keys[GLFW_KEY_Y]) dogPosZ -= 0.0001f;
	if (keys[GLFW_KEY_G]) dogPosX -= 0.0001f;
	if (keys[GLFW_KEY_J]) dogPosX += 0.0001f;
	if (keys[GLFW_KEY_6]) dogPosY -= 0.0001f;
	if (keys[GLFW_KEY_7]) dogPosY += 0.0001f;
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])    camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])   camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])   camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])  camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			interpolation();
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
	}

	// Guardar keyframe manualmente (K)
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		pendingSave = true; 
	}


	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		pendingLoad = true;
	}


	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(0.2f, 0.8f, 1.0f);
		}
		else
		{
			Light1 = glm::vec3(0);
		}
	}
}

void Animation()
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps)
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)
			{
				printf("termina animacion\n");
				playIndex = 0;
				play = false;
			}
			else
			{
				i_curr_steps = 0;
				interpolation();
			}
		}
		else
		{

			dogPosX += KeyFrame[playIndex].incX;
			dogPosY += KeyFrame[playIndex].incY;
			dogPosZ += KeyFrame[playIndex].incZ;

			rotDog += KeyFrame[playIndex].rotDogInc;
			bodyTilt += KeyFrame[playIndex].bodyTiltInc;
			bodySpin += KeyFrame[playIndex].bodySpinInc;

			head += KeyFrame[playIndex].headInc;
			tail += KeyFrame[playIndex].tailInc;


			legFL += KeyFrame[playIndex].legFLInc;
			legFR += KeyFrame[playIndex].legFRInc;
			legBL += KeyFrame[playIndex].legBLInc;
			legBR += KeyFrame[playIndex].legBRInc;

			i_curr_steps++;
		}
	}
}


void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}