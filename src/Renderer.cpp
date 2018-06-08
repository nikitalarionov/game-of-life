#include "Renderer.h"

static uint16_t GridWidth = 20;

Renderer::Renderer(World& world, RenderTarget& renderTarget) : world(world), renderTarget(renderTarget),
                                                               view(), rectangle(), circle(8) {
    view.reset(FloatRect(0, 0, world.GetWidth() * GridWidth, world.GetHeight() * GridWidth));
    rectangle.setSize(Vector2f(world.GetWidth() * GridWidth, world.GetHeight() * GridWidth));
    rectangle.setFillColor(Color(60, 130, 190, 192));
    circle.setFillColor(Color(250, 250, 250));
}

void Renderer::Move(float dx, float dy) {
    view.move(dx, dy);
}

void Renderer::Render() {
    auto previousView = renderTarget.getView();
    renderTarget.setView(view);
    renderTarget.draw(rectangle);
    for (uint32_t y = 0; y < world.GetHeight(); y++) {
        for (uint32_t x = 0; x < world.GetWidth(); x++) {
            if (world.GetCell(x, y)) {
                circle.setPosition(x * GridWidth + 2, y * GridWidth + 2);
                renderTarget.draw(circle);
            }
        }
    }
    renderTarget.setView(previousView);
}