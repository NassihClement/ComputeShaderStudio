void main() {
    uint x = gl_GlobalInvocationID.x;
    uint y = gl_GlobalInvocationID.y;
    uint p = x + y * WSX;
    
    // Circle parameters
    float centerX = WSX / 2.0;
    float centerY = WSY / 2.0;
    float radius = 70.0;
    
    // Angle de rotation
    float angle = float(step) * 0.1;
    
    // Calculate distance from current pixel to circle center
    float dx = float(x) - centerX;
    float dy = float(y) - centerY;
    float distance = sqrt(dx * dx + dy * dy);
    
    // Calculate angle of current pixel relative to center
    float pixelAngle = atan(dy, dx);
    
    // Width of the line in radians
    float lineWidth = 0.1;
    
    // Check if pixel is on the rotating line
    bool onLine = abs(mod(pixelAngle - angle, 2.0 * 3.14159)) < lineWidth;
    
    // Inner circle parameters with pulsing effect
    float baseInnerRadius = 18.0;
    float pulseAmplitude = 3.0; // Change in radius (20 to 23)
    float pulseFrequency = 1.5; // Réduit de 3.0 à 1.5 pour un pulsage plus lent
    float innerRadius = baseInnerRadius + pulseAmplitude; //* sin(float(step) * pulseFrequency * 0.1); //PULSAGE
    
    // Border circle parameters
    float borderWidth = 2.0;
    float borderRadius = innerRadius + 15.0; // Un peu plus grand que le cercle intérieur
    
    // Moving circle parameters (3 circles)
    float movingCircleRadius = 5.0;
    // Premier cercle (position originale)
    float movingCircleX = centerX + borderRadius * cos(angle);
    float movingCircleY = centerY + borderRadius * sin(angle);
    float movingCircleDistance = sqrt(pow(float(x) - movingCircleX, 2.0) + pow(float(y) - movingCircleY, 2.0));
    
    // Deuxième cercle (décalé de 120 degrés)
    float movingCircle2X = centerX + borderRadius * cos(angle + 2.0944); // 2.0944 = 2π/3
    float movingCircle2Y = centerY + borderRadius * sin(angle + 2.0944);
    float movingCircle2Distance = sqrt(pow(float(x) - movingCircle2X, 2.0) + pow(float(y) - movingCircle2Y, 2.0));
    
    // Troisième cercle (décalé de 240 degrés)
    float movingCircle3X = centerX + borderRadius * cos(angle + 4.1888); // 4.1888 = 4π/3
    float movingCircle3Y = centerY + borderRadius * sin(angle + 4.1888);
    float movingCircle3Distance = sqrt(pow(float(x) - movingCircle3X, 2.0) + pow(float(y) - movingCircle3Y, 2.0));

    // Croissant parameters pour les trois cercles
    float crescentRadius = 5.0;
    float crescentOffset = 2.0;
    
    // Croissants pour chaque cercle mobile
    // Croissant 1
    float crescent1MainDist = sqrt(pow(float(x) - (movingCircleX), 2.0) + 
                                 pow(float(y) - (movingCircleY - crescentRadius), 2.0));
    float crescent1SecDist = sqrt(pow(float(x) - (movingCircleX + crescentOffset), 2.0) + 
                                pow(float(y) - (movingCircleY - crescentRadius), 2.0));
    
    // Croissant 2
    float crescent2MainDist = sqrt(pow(float(x) - (movingCircle2X), 2.0) + 
                                 pow(float(y) - (movingCircle2Y - crescentRadius), 2.0));
    float crescent2SecDist = sqrt(pow(float(x) - (movingCircle2X + crescentOffset), 2.0) + 
                                pow(float(y) - (movingCircle2Y - crescentRadius), 2.0));
    
    // Croissant 3
    float crescent3MainDist = sqrt(pow(float(x) - (movingCircle3X), 2.0) + 
                                 pow(float(y) - (movingCircle3Y - crescentRadius), 2.0));
    float crescent3SecDist = sqrt(pow(float(x) - (movingCircle3X + crescentOffset), 2.0) + 
                                pow(float(y) - (movingCircle3Y - crescentRadius), 2.0));

    // Draw circle with line and inner circle
    if (distance < radius) {
        if ((crescent1MainDist < crescentRadius && crescent1SecDist > crescentRadius - 1.0) ||
            (crescent2MainDist < crescentRadius && crescent2SecDist > crescentRadius - 1.0) ||
            (crescent3MainDist < crescentRadius && crescent3SecDist > crescentRadius - 1.0)) {
            data_0[p] = 0xFF000000; // Black crescents
        } else if (movingCircleDistance < movingCircleRadius || 
                  movingCircle2Distance < movingCircleRadius ||
                  movingCircle3Distance < movingCircleRadius) {
            data_0[p] = 0xFF000000; // Black moving circles
        } else if (distance < innerRadius) {
            data_0[p] = 0xFF000000; // Black inner circle
        } else if (distance < borderRadius && distance > borderRadius - borderWidth) {
            data_0[p] = 0xFF000000; // Black border
        } else if (onLine) {
            //data_0[p] = 0xFF000000; // Black line
        } else {
            data_0[p] = 0xFF0000FF; // Red circle
        }
    } else {
        data_0[p] = 0xFFFFFFFF; // White background
    }
}
