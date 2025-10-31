#include "Includes/header.h"

std::vector<double> cameraPos({0.0f, 0.0f,  3.0f});
std::vector<double> cameraFront({0.0f, 0.0f, -1.0f});
std::vector<double> cameraUp({0.0f, 1.0f,  0.0f});

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// unsigned int indices[] = {
	// 	0, 1, 3,
	// 	1, 2, 3
	// };

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	// glGenBuffers(1, EBO);

	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

void defineMatrices(Shader shad) {
	// Matrix<double> model = Matrix<double>::rot((float)glfwGetTime(), {0.5,1.,0.});
	const float radius = 10.;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	Matrix<double> view = Matrix<double>::lookAt({camX, 0., camZ}, {0.,0.,0.}, {0.,1.,0.});
	Matrix<double> projection = Matrix<double>::perspective(degreeToRad(45.), 800. /  600., 0.1, 100.);
	// int modelLoc = glGetUniformLocation(shad.getID(), "model");
	// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.toGLArray(true));
	int viewLoc = glGetUniformLocation(shad.getID(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.toGLArray(true));
	int projectionLoc = glGetUniformLocation(shad.getID(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.toGLArray(true));
}

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
	
	try {
		Texture tex("./Textures/BlackLodge.png", {.params = {GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR}});
		Texture tex2("./Textures/awesomeface.png", {.type = GL_RGBA, .params = {GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR}});
		// Shader shad((std::string)"ShadersFiles/VertexTexMatShader01.vs", (std::string)"ShadersFiles/FragTexShader01.gsls");
		Shader shad((std::string)"ShadersFiles/VertexMVP.vs", (std::string)"ShadersFiles/FragTexShader01.gsls");
		Matrix<double> cubePositions({
			{ 0.0f,  0.0f,  0.0f}, 
			{ 2.0f,  5.0f, -15.0f}, 
			{-1.5f, -2.2f, -2.5f},  
			{-3.8f, -2.0f, -12.3f},  
			{ 2.4f, -0.4f, -3.5f},  
			{-1.7f,  3.0f, -7.5f},  
			{ 1.3f, -2.0f, -2.5f},  
			{ 1.5f,  2.0f, -2.5f}, 
			{ 1.5f,  0.2f, -1.5f}, 
			{-1.3f,  1.0f, -1.5f}
		});
		unsigned int VAO, VBO, EBO;
		drawRectangles(&VAO, &VBO, &EBO);
		
		shad.use();
		glEnable(GL_DEPTH_TEST);
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
			// glActiveTexture(GL_TEXTURE1);
			// glBindTexture(GL_TEXTURE_2D, tex2.id());
			
			shad.use();
			defineMatrices(shad);
			glBindVertexArray(VAO);
			for(unsigned int i = 0; i < 10; i++)
			{
				Matrix<double> model = Matrix<double>::translation(cubePositions[i]);
				float angle = 20.0f * i; 
				Matrix<double> rot = Matrix<double>::rot(glfwGetTime(), {1.0f, 0.3f, 0.5f});
				model *= rot;
				shad.setMat("model", model.toGLArray());

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			// Clear the color buffer
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// glDrawArrays(GL_TRIANGLES, 0, 36);
			glfwSwapBuffers(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		glfwTerminate();
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
		exit(0);
	}
    return 0;
}
