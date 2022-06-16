// Handles all grid functionality.
//
// Created by loona on 06/06/22.
//

#include "grid.h"
#include <cmath>

std::vector<int> grid::convertCoords(std::vector<int> gridCoords) {
    /*
     * Converts a pair of coordinates.
     *
     * The coordinates on the grid represent blocks. each block is blockSize(16px).
     * Therefore, we must convert our desired gridCoords, which represent the block's coordinates to
     * the drawCoords, which represents the coordinates on the screen that match the gridCoords.
     *
     * Example:
     *  // we want to draw the point 0,0. it is located on point: 960, 540.
     *  (0,0) -> (960, 540)
     * */
    return {
            midPoint[0] + (int)(gridCoords[0] * zoomFactor * blockSize),
            midPoint[1] - (int)(gridCoords[1] * zoomFactor * blockSize)
    };
}

std::vector<int> grid::getGridDimensions(){
    /*
     * Determines the size of the grid given the zoom factor and block size.
     *
     * The grid is an abstraction. its points and the drawCoords are not one-to-one. so we dont know if a coordinate is
     * off-screen or not.
     * We want to render all points onscreen and not the ones off-screen.
     *
     * This function uses the blockSize, midPoint and zoomFactor to determine the dimensions of the grid.
     * this dimensions is how far the grid goes in the x and y directions. this is the number of blocks drawn.
     * All of these blocks will be visible.
     *
     * Example:
     *  blockSize = 32, zoomFactor = 1.0, midPoint = [960, 540]
     *  -> [30, 17]
     *  // 30 blocks can partially/fully fit in the -x or +x direction.
     *  // 17 blocks can partially/fully fit within the -y or +y direction.
     *
     * */
    return {
            static_cast<int>(ceil(midPoint[0] / (blockSize * zoomFactor))),
            static_cast<int>(ceil(midPoint[1] / (blockSize * zoomFactor)))
    };
}

void grid::setZoom(float delta) {
    /*
     * Adjusts the zoomFactor global constant.
     *
     * We use this when we zoom in and out during the game.
     * Is triggered when we scroll the vertical mouse wheel.
     *
     * the delta is a float. either -0.25 or +0.25 .
     *
     * To prevent the zoom factor from reaching or falling below 0, we set a limit.
     * If the zoom factor is 0.25 and the delta is negative, do not scroll out further.
     *
     * Additionally, there is a limit on zooming in.
     * The zoom factor cannot exceed 4.0.
     * if it reaches 4.0 and delta >0, do not scroll in further
     *
     * Otherwise, the scroll wheel will simply add the delta to the zoomFactor.
     *
     * TODO:
     *  zooming is kinda slow. maybe check fps?
     * */

    // does nothing if we try to zoom in/out beyond the limits
    if (delta < 0 and zoomFactor ==0.25f);
    else if (delta > 0 and zoomFactor == 4.0f);

    else zoomFactor += delta; // otherwise, just zoom freely

    // std::cout << zoomFactor << std::endl;
}

void grid::drawMidpoint(sf::RenderWindow *window) { // draws the midpoint
    // makes 2 rects in the centre.
    // we make 2 for the sake of visibility

    // the first, larger rect
    sf::RectangleShape mid;
    mid.setPosition(midPoint[0], midPoint[1]);
    mid.setOrigin(8,8);
    mid.setFillColor(sf::Color::Black);
    mid.setSize(sf::Vector2<float>(16,16));
    window->draw(mid);

    // the smaller rect
    sf::RectangleShape mid2;
    mid2.setPosition(midPoint[0], midPoint[1]);
    mid2.setOrigin(4,4);
    mid2.setFillColor(sf::Color::White);
    mid2.setSize(sf::Vector2<float>(8,8));
    window->draw(mid2);
}

void grid::calcFrameData(sf::Clock *clock) {
    /*
     * Calculates all the frame data.
     *
     * This includes frametimes and FPS
     * */

    frameTime = clock->restart().asSeconds(); // frametime is the time from 1 frame to the next. in seconds
    FPS = 1/frameTime; // FPS is 1/frametime
}

void grid::drawFPS(sf::RenderWindow *window) {
    /*
     * Draws the FPS to the screen.
     *
     * Starts by loading the font file.
     *
     * Then sets the text and draws it
     * */

    sf::Font font;
    font.loadFromFile("../../assets/fonts/blockgame.ttf"); // TODO: error handle this

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setString(std::to_string((int)FPS)); // sets the text of the string to the FPS value
    fpsText.setCharacterSize(24); // size in pixels
    fpsText.setFillColor(sf::Color::White);

    window->draw(fpsText);
}
