typedef struct
{
    int x, y;
    Texture2D texture;
} Floor;

void DrawFloor(Floor floor);

void DrawFloor(Floor floor)
{
    DrawTextureEx(floor.texture, (Vector2){floor.x, floor.y}, 0, 1, RAYWHITE);
}