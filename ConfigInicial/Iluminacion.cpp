/* Barco Núñez Claudia Citlali
* No. de Cuenta: 422067621
* Fecha: 24-03-2026
* Practica 8. Materiales e Iluminación
/*/

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

float orbitAngle = 0.0f;
float orbitSpeed = 0.8f;

bool lunaActiva = false;
bool solActivo = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "P8. Claudia Barco", nullptr, nullptr);
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Shaders
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader moonShader("Shader/modelLoading.vs", "Shader/moonColor.frag");
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );

    Model red_dog((char*)"Models/dog/RedDog.obj");
    Model moonModel((char*)"Models/moon/moon.obj");
    Model sun((char*)"Models/sun/sun.obj");
    Model cat((char*)"Models/cat/12221_Cat_v1_l3.obj");
    Model light((char*)"Models/light/light.obj");
    Model mountain((char*)"Models/mountain/mountain.obj");
    Model plant((char*)"Models/plant/FlowerPot.obj");
    Model sky((char*)"Models/sky/skywall.obj");
    Model bench((char*)"Models/bench/bench.obj");
    Model ground((char*)"Models/ground/grass.obj");


    glm::mat4 projection = glm::perspective(camera.GetZoom(),(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Textura del perro
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    image = stbi_load("Models/dog/Texture_albedo.jpg", &textureWidth, &textureHeight, &nrChannels, 0);
    if (image)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();

        // Posiciones orbitales
        float orbitRadius = 0.75f;
        glm::vec3 posSol = glm::vec3(
            orbitRadius * cos(orbitAngle),
            orbitRadius * sin(orbitAngle),
            0.0f);

        glm::vec3 posLuna = glm::vec3(
            orbitRadius * cos(orbitAngle + glm::pi<float>()),
            orbitRadius * sin(orbitAngle + glm::pi<float>()),
            0.0f);

        // pivote
        glm::mat4 modelBench = glm::mat4(1.0f);
        modelBench = glm::translate(modelBench, glm::vec3(0.0f, 0.0f, -2.0f));
        modelBench = glm::rotate(modelBench, glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f));
        modelBench = glm::scale(modelBench, glm::vec3(9.0f));

        lightingShader.Use();

        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
            camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Sol
        if (solActivo)
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"), posSol.x, posSol.y, posSol.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.4f, 0.4f, 0.3f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 1.0f, 0.95f, 0.8f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 0.8f);
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.0f, 0.0f, 0.0f);
        }

        // Luna
        if (lunaActiva)
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.position"), posLuna.x, posLuna.y, posLuna.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.ambient"), 0.1f, 0.2f, 0.6f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.diffuse"), 0.1f, 0.15f, 0.4f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.specular"), 0.1f, 0.4f, 0.6f);
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.position"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.ambient"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.diffuse"), 0.0f, 0.0f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "lightMoon.specular"), 0.0f, 0.0f, 0.0f);
        }

        // Material
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.6f, 0.5f, 0.4f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.3f, 0.3f, 0.3f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // Banca pivote 
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelBench));
        bench.Draw(lightingShader);

        // Perro
        glm::mat4 modelRedDog = glm::mat4(1.0f);;
        modelRedDog = glm::translate(modelRedDog, glm::vec3(1.0f, 0.0f, 1.0f));
        modelRedDog = glm::scale(modelRedDog, glm::vec3(1.5f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelRedDog));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(lightingShader.Program, "texture_diffuse"), 0);
        red_dog.Draw(lightingShader);

        // Gato 
        glm::mat4 modelCat = glm::mat4(1.0f);;
        modelCat = glm::translate(modelCat, glm::vec3(-1.0f, -0.5f, 1.0f));
        modelCat = glm::rotate(modelCat, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelCat = glm::scale(modelCat, glm::vec3(0.03f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCat));
        cat.Draw(lightingShader);

        // Farol 
        glm::mat4 modelLight = glm::mat4(1.0f); modelBench;
        modelLight = glm::translate(modelLight, glm::vec3(0.0f, 0.0f, -6.0f));
        modelLight = glm::scale(modelLight, glm::vec3(0.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLight));
        light.Draw(lightingShader);

        // Montaña 
        glm::mat4 modelMountain = glm::mat4(1.0f);
        modelMountain = glm::translate(modelMountain, glm::vec3(0.0f, -1.0f, -40.0f));
        modelMountain = glm::scale(modelMountain, glm::vec3(5.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMountain));
        mountain.Draw(lightingShader);

        // Cielo
        glm::mat4 modelSky = glm::mat4(1.0f);
        modelSky = glm::translate(modelSky, glm::vec3(0.0f, -10.0f, -50.0f));
        modelSky = glm::scale(modelSky, glm::vec3(50.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSky));
        sky.Draw(lightingShader);

        // Piso 
        glm::mat4 modelGround = glm::mat4(1.0f);
        modelGround = glm::translate(modelGround, glm::vec3(0.0f, -1.5f, 0.0f));
        modelGround = glm::scale(modelGround, glm::vec3(13.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelGround));
        ground.Draw(lightingShader);

		// Sol y Luna - LUCES
        shader.Use();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Sol
        if (solActivo)
        {

            glm::mat4 localSunModel = glm::mat4(1.0f);
            localSunModel = glm::rotate(localSunModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            localSunModel = glm::translate(localSunModel, posSol);
            localSunModel = glm::scale(localSunModel, glm::vec3(0.02f));

            glm::mat4 inheritedSolModel = modelBench * localSunModel;

            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(inheritedSolModel));
            sun.Draw(shader);
        }

		// Luna
        if (lunaActiva)
        {

            glm::mat4 localMoonModel = glm::mat4(1.0f);
            localMoonModel = glm::rotate(localMoonModel, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            localMoonModel = glm::translate(localMoonModel, posLuna);
            localMoonModel = glm::scale(localMoonModel, glm::vec3(0.25f));

            glm::mat4 inheritedMoonModel = modelBench * localMoonModel;

            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(inheritedMoonModel));
            moonModel.Draw(shader);
        }
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (keys[GLFW_KEY_O])
        orbitAngle += orbitSpeed * deltaTime;
    if (keys[GLFW_KEY_P])
        orbitAngle -= orbitSpeed * deltaTime;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)   keys[key] = true;
        if (action == GLFW_RELEASE) keys[key] = false;
    }

    // J = activar/desactivar sol
    if (key == GLFW_KEY_J && action == GLFW_PRESS)
        solActivo = !solActivo;

    // M = activar/desactivar luna
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
        lunaActiva = !lunaActiva;
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