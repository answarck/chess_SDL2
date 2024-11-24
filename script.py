import os

l = {"w", "b"}
k = {"k","q","p","n","b","r"}
for i in l:
    for j in k:
        os.system(f"curl https://www.chess.com/chess-themes/pieces/neo/300/{i}{j}.png > ./assets/{i}{j}.png")
