#include "Includes/header.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void drawTriangle() {
	float vertices[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	
	// Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void drawRectangles(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO) {
	float vertices[] = {
		// positions        // texture coords
		0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left 
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

GLFWwindow* initWindow() {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	return glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
}

void updateColor(Shader shad) {
	// update the uniform color
    float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
	shad.setFloats("ourColor", 0.0f, greenValue, 0.0f, 1.0f);
    // int vertexColorLocation = glGetUniformLocation(shad.getID(), "ourColor");
    // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}
#include <array>
int main()
{
	GLFWwindow* window = initWindow();
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// CreateShader vertex(3);
	// CreateShader fragment(std::vector<float>({1.0f, 0.5f, 0.1f}));
	// CreateShader fragColors;
	try {
		Texture tex("./Textures/container.jpg", {.params = {GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR}});
		Texture tex2("./Textures/awesomeface.png", {.type = GL_RGBA, .params = {GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR}});
		Shader shad((std::string)"ShadersFiles/VertexTexMatShader01.vs", (std::string)"ShadersFiles/FragTexShader01.gsls");
		
		// drawTriangle();
		// trans = trans.scale(std::vector<float>({0.5,0.5,0.5}));
		
		Matrix<double> d = Matrix<double>::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
		std::cout << d << std::endl;
		unsigned int VAO, VBO, EBO;
		drawRectangles(&VAO, &VBO, &EBO);
		
		shad.use();
		glUniform1i(glGetUniformLocation(shad.getID(), "texture1"), 0);
		shad.setInt("texture2", 1);
		while(!glfwWindowShouldClose(window))
		{
			processInput(window);
			// Set the clear color (RGBA)
			glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex.id());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex2.id());
			
			// Matrix<float> rot(4, 4, true);
			shad.use();
			Matrix<float> trans(std::vector<float>({0.5,-0.5,0.0}));
			Matrix<float> rot = Matrix<float>::rot((float)glfwGetTime(), std::vector<float>({0.0, 0.0, 1.0}));
			trans *= rot;
			trans = trans.scale(std::vector<float>({0.5,0.5,0.5}));
			unsigned int transformLoc = glGetUniformLocation(shad.getID(), "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans.toGLArray(true));
			glBindVertexArray(VAO);
			// updateColor(shad);
			// Clear the color buffer
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// glDrawArrays(GL_TRIANGLES, 0, 3);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
		exit(0);
	}
    return 0;
}
