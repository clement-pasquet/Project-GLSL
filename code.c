// Please, copy/paste the code on https://www.shadertoy.com/new if you want it to works

vec3 palette ( float t) { // pas compris ne pas demander
    vec3 a = vec3(0.8, 0.5, 0.4);
    vec3 b = vec3(0.2, 0.4, 0.2);
    vec3 c = vec3(2.0, 1.0, 1.0);
    vec3 d = vec3(0.00, 0.25, 0.25);
    
    return a +b*cos(3.14*2.0*(c*t+d) );
    
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) // on crée une animation, un "shader" directement en opengl
{

    vec2 uv = (fragCoord) / iResolution.xy * 2.0 - 1.0; // chaque pixel a un placement relatif à la taille de l'ecran (ex : 10% de x )
    uv.x *= iResolution.x / iResolution.y;
    vec2 uv0 = uv; 
    vec3 finalColor = vec3(0.0); //creation d'un vecteur a 3 dimensions pour en afficher plusieurs
    
    for (float i = 0.0 ; i <  4.; i++ ) { //boucle pour créer plusieurs vecteurs
        uv*=3.14;
        uv = fract(uv);
        uv-=0.5; // offset qui permet que les coordonnées soient au centre et pas en bas a gauche

        float dist = length(uv) * exp(-length(uv0)); // length == distance par rapport au milieu

        vec3 maPalette = palette(length(uv0) *i*.4 + iTime * 0.4);

        dist = sin(dist*3. + iTime)/3.;
        dist = abs(dist);

        dist = pow(0.01 / dist, 1.2); // on utilise la puissance pour moins afficher les sombres et plus les clairs
        
        finalColor += maPalette*dist; // on additionne le vecteur actuel au vecteur final
    }

    
    
    //dist = smoothstep(0.1,0.8,dist);

    // Output to screen
    fragColor = vec4(finalColor,0.5);
}
