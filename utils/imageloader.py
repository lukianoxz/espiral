from PIL import Image

img_file = str(input('Type here the name of your image: '))
img = Image.open(img_file).convert('RGBA')
img_w, img_h = img.size

texture = f'{img_w};X'

for y in range(img_h):
    for x in range(img_w):
        r, g, b, a = img.getpixel((x, y))
        texture += f'{r:03d}{g:03d}{b:03d}{a:03d}'

texture_name = img_file.split('.')[0]
texture_name += '.txt'

with open(texture_name, 'w') as f:
    f.write(texture)

print(f'Texture salved in {texture_name}')