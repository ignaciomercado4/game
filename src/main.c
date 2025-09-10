#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./core/window.h"
#include "./core/input.h"
#include "./graphics/shader.h"
#include "./math/math_n.h"
#include "./game/wall.h"
#include "./graphics/light.h"
#include "./game/camera.h"
#include "./core/utils.h"
#include "./graphics/VAO.h"
#include "./graphics/VBO.h"
#include "./game/NPC.h"
#include "./game/level.h"
#include "./game/floor.h"

float QUAD_VERTICES[] =
    {
        // x      y      z     r     g     b     nx    ny    nz   uvx
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f};
unsigned int QUAD_INDICES[] =
    {
        0, 1, 3,
        1, 2, 3};
float CUBE_VERTICES[] =
    {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f};
unsigned int CUBE_INDICES[] =
    {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        0, 3, 7,
        7, 4, 0,
        1, 5, 6,
        6, 2, 1,
        0, 1, 5,
        5, 4, 0,
        3, 2, 6,
        6, 7, 3};

Camera camera = {
    .free = false,
    .yaw = -135.0f,
    .pitch = -35.0f,
    .speed = 2.0f,
    .FOV = 70.0f,
    .eye = VEC3(4.0f, 3.0f, 3.0f),
    .center = VEC3(0.0f, 0.0f, 0.0f),
    .up = VEC3(0.0f, 1.0f, 0.0f)};

int main()
{
    GLFWwindow *window = create_window(1920, 1080, "dajlsdkjad");

    Level level_test = {
        .NPC_count = 1,
        .floor_count = 1,
        .light_count = 1,
        .wall_count = 4,
        .walls = {
            {.start_coordinates = {-5.0f, 0.0f, -5.0f}, .end_coordinates = {-5.0f, 4.0f, 5.0f}, .texture = load_texture("./resources/textures/wallpaper.png")},
            {.start_coordinates = {-5.0f, 0.0f, 5.0f}, .end_coordinates = {5.0f, 4.0f, 5.0f}, .texture = load_texture("./resources/textures/wallpaper.png")},
            {.start_coordinates = {5.0f, 0.0f, 5.0f}, .end_coordinates = {5.0f, 4.0f, -5.0f}, .texture = load_texture("./resources/textures/wallpaper.png")},
            {.start_coordinates = {5.0f, 0.0f, -5.0f}, .end_coordinates = {-5.0f, 4.0f, -5.0f}, .texture = load_texture("./resources/textures/wallpaper.png")},
        },
        .lights = {{.color = VEC3(1.0f, 0.0f, 0.0f), .position = VEC3(-4.0f, 0.5f, -4.0f)}},
        .floors = {{.start_coordinates = {-5.0f, 0.0f, 5.0f}, .end_coordinates = {5.0f, 0.0f, -5.0f}, .texture = load_texture("./resources/textures/floor_wood.png")}},
        .npcs = {{.position = VEC3(0.0f, 1.0f, 0.0f), .texture = load_texture("./resources/textures/X.png")}},
    };

    save_level("./levels/level_test.bin", &level_test);
    Level lev = load_level_from_file("./levels/level_test.bin");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDebugMessageCallback(gl_debug_callback, NULL);

    /*EVERYTHING*/
    VAO quad_vao = vao_create();
    vao_bind(quad_vao);

    VBO quad_vbo = vbo_create(QUAD_VERTICES, sizeof(QUAD_VERTICES), GL_ARRAY_BUFFER);
    VBO quad_ebo = vbo_create(QUAD_INDICES, sizeof(QUAD_INDICES), GL_ELEMENT_ARRAY_BUFFER);

    vao_bind(quad_vao);
    vbo_bind(quad_vbo);

    vao_set_vertex_attrib_data(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)0);
    vao_set_vertex_attrib_data(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(3 * sizeof(float)));
    vao_set_vertex_attrib_data(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(6 * sizeof(float)));
    vao_set_vertex_attrib_data(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *)(9 * sizeof(float)));

    /*LIGHT*/
    VAO light_vao = vao_create();
    vao_bind(light_vao);

    VBO light_vbo = vbo_create(CUBE_VERTICES, sizeof(CUBE_VERTICES), GL_ARRAY_BUFFER);
    VBO light_ebo = vbo_create(CUBE_INDICES, sizeof(CUBE_INDICES), GL_ELEMENT_ARRAY_BUFFER);

    vao_bind(light_vao);
    vbo_bind(light_vbo);

    vao_set_vertex_attrib_data(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    /*SHADERS*/
    unsigned int wall_shader = load_shader("./resources/shaders/wall.vert", "./resources/shaders/wall.frag");
    unsigned int light_shader = load_shader("./resources/shaders/light.vert", "./resources/shaders/light.frag");
    unsigned int NPC_shader = load_shader("./resources/shaders/NPC.vert", "./resources/shaders/NPC.frag");
    unsigned int floor_shader = load_shader("./resources/shaders/floor.vert", "./resources/shaders/floor.frag");

    /*TEXTURES*/

    /*time*/
    float last_frame = 0.0f;
    float delta_time = 0.0f;

    Floor floor_test = {
        .start_coordinates = {-5.0f, -1.0f, 5.0f},
        .end_coordinates = {5.0f, -1.0f, -5.0f},
        .texture = load_texture("./resources/textures/floor_wood.png")};

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        process_keyboard_input(window, &camera, delta_time);
        camera_point(&camera, window, delta_time);

        /*EVERYTHING*/
        draw_level(&lev, &camera, wall_shader, floor_shader, light_shader, NPC_shader, quad_vao, light_vao);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}