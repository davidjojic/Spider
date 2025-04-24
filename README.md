# Spider Follows Mouse Simulation

This project simulates a spider that follows the mouse cursor on the screen. The spider consists of multiple legs, represented by random dots scattered around the screen. The spider tries to follow the cursor, but if any leg extends too far, it "breaks" and reconnects to the closest free point, with a maximum of 8 connections.

## Key Features:
- **Spider Movement**: The spider attempts to follow the mouse cursor in real-time.
- **Leg Behavior**: The spider has up to 8 legs (connections) that move toward the mouse. If a leg extends too far, it breaks and reconnects to the closest free spot.
- **Random Dots**: The screen is filled with random dots, representing potential connection points for the spider's legs.
- **Leg Extension Limit**: Each leg can extend up to a maximum distance before breaking and reconnecting to a nearby spot.

## Technologies Used:
- **C++**
- **SFML 2.6.2**: For graphics rendering and event handling.
