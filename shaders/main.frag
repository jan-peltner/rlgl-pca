#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
out vec4 finalColor;
uniform float time;
uniform vec4 colors[10];
uniform vec2 resolution;

void main()
{
    // Create a smoothly varying value between 0 and 10 based on position and time
    float colorPosition = mod(gl_FragCoord.x / 100.0 + time * 0.5, 10.0);
    
    // Find the two colors to interpolate between
    int colorIndex1 = int(floor(colorPosition)) % 10;
    int colorIndex2 = int(floor(colorPosition) + 1) % 10;
    
    // Calculate the interpolation factor (0.0 to 1.0)
    float mixFactor = fract(colorPosition);
    
    // Mix the two colors
    finalColor = mix(colors[colorIndex1], colors[colorIndex2], mixFactor);
}
