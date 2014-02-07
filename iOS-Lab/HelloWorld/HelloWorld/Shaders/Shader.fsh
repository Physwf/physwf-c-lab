//
//  Shader.fsh
//  HelloWorld
//
//  Created by Joe Physwf on 2/7/14.
//  Copyright (c) 2014 Joe Physwf. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
