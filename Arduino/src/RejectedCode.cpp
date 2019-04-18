  /*
  while(1)
  {
        timer = millis();
        
        int *y = ros.readID();
        int *x = ros.readID()+1;
        int *a = ros.readID()+2;
        angpos = *a;
        angpos = angpos;
        angtar = 0;

        angerr = Pidxya.error(angtar,angpos);
        
        PIDa.Compute();
        if (angerr<-5)
        {
          shutdowntime = 0;                             // keep a running count of time within loop
          if (aCmd>0)
          {
            motor.rotateRight(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(aCmd<0)
          {
            motor.rotateRight(-1*aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else if(angerr>5)
        {
          shutdowntime = 0;                             // keep a running count of time within loop
          if (aCmd>0)
          {
            motor.rotateLeft(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(aCmd<0)
          {
            motor.rotateLeft(-1*aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else
        {
          shutdowntime += (millis()- timer)*10;           

          if( shutdowntime > 50)                  // if running count exceed 2 cycles break out of loop
          {                                         
            motor.Stop();
            break;
          }
        }
        Serial.print(angtar);
        Serial.print(" \t ");
        Serial.print(angpos);
        Serial.print(" \t ");
        Serial.println(aCmd);
        timeBetFrames = millis() - timer;
  }
  
  delay(1000);
/*
  while(1)
  {
        timer = millis();
        int *x = ros.readID();
        int *y = ros.readID()+1;
        int *a = ros.readID()+2;
        xpos = *x;
        
        xtar = 0;

        xerr = Pidxya.error(xtar,xpos);
        
        PIDx.Compute();
        if (xerr>0.5)
        {
          if (xCmd>0)
          {
            motor.Left(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(xCmd<0)
          {
            motor.Left(-1*xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else if(xerr<-0.5)
        {
          if (xCmd>0)
          {
            motor.Right(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(xCmd<0)
          {
            motor.Right(-1*xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else
        {
           motor.Stop();
           break;
        }
        Serial.print(xtar);
        Serial.print(" \t ");
        Serial.print(xpos);
        Serial.print(" \t ");
        Serial.println(xCmd);
        timeBetFrames = millis() - timer;
  }
  
  delay(1000);
  
  while(1)
  {
        timer = millis();
        int *y = ros.readID();
        int *x = ros.readID()+1;
        int *a = ros.readID()+2;
        ypos = *y;  
        ypos = ypos;  
        ytar = 0;

        yerr = Pidxya.error(ytar,ypos);
        
        PIDy.Compute();
        if (yerr>10)
        {
          shutdowntime = 0;                             // keep a running count of time within loop
          if (yCmd>0)
          {
            motor.Backward(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(yCmd<0)
          {
            motor.Backward(-1*yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else if(yerr<-10)
        {
          shutdowntime = 0;                             // keep a running count of time within loop
          if (yCmd>0)
          {
            motor.Forward(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(yCmd<0)
          {
            motor.Forward(-1*yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
        }
        else
        {
          shutdowntime += (millis()- timer)*10;           

          if( shutdowntime > 50)                  // if running count exceed 2 cycles break out of loop
          {                                         
            motor.Stop();
            break;
          }
        }
        Serial.print(ytar);
        Serial.print(" \t ");
        Serial.print(ypos);
        Serial.print(" \t ");
        Serial.println(yCmd);
        timeBetFrames = millis() - timer;
  }
  */
  
 /*
  runn = 1;
  while(runn != 0)
  {
     ros.readTar();
     
     int pathlenght = ros.Path[0];
     int X[pathlenght],Y[pathlenght];
     for(int x = 1;x<ros.numPoints/2;x++)
     {
        X[x-1] = ros.Path[2*x - 1];
     }
     for(int x = 1;x<(ros.numPoints)/2;x++)
     {
       Y[x-1] = ros.Path[2*x];
     }

     while(i<(ros.numPoints/2)-1)
     {

        xtar = X[i];
        ytar = Y[i];
     
        while(1)
        {
          ros.readPos();

          angpos = ros.Position[3];
          angpos = angpos/100;

          int x = xtar - xpos;
          int y = ytar - ypos;
         
          angtar = atan(x/y);

          angerr = Pidxya.error(angtar,angpos);
          
          PIDa.Compute();
          if (angerr>0)
          {
            motor.rotateLeft(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(angerr<0)
          {
            motor.rotateRight(aCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(angtar);
          Serial.print(" \t ");
          Serial.print(angpos);
          Serial.print(" \t ");
          Serial.println(aCmd);
        }
        
        while(1)
        {
          ros.readPos();

          xpos = ros.Position[1];

          xerr = Pidxya.error(xtar,xpos);
        
          PIDx.Compute();
  
          if (xerr>0)
          {
             motor.Forward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(xerr<0)
          {
            motor.Backward(xCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(xtar);
          Serial.print(" \t ");
          Serial.print(xpos);
          Serial.print(" \t ");
          Serial.println(xCmd);
        }
        
        while(1)
        {
          ros.readPos();

          ypos = ros.Position[2];

          yerr = Pidxya.error(ytar,ypos);
          
          PIDy.Compute();
          
          if (yerr>0)
          {
            motor.Left(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else if(yerr<0)
          {
            motor.Right(yCmd,timeBetFrames,M1encoderPos,M2encoderPos,M3encoderPos,M4encoderPos);
          }
          else
          {
            motor.Stop();
            break;
          }
          Serial.print(ytar);
          Serial.print(" \t ");
          Serial.print(ypos);
          Serial.print(" \t ");
          Serial.println(yCmd);
        }
        
        if(xerr == 0 && yerr == 0 && angerr == 0)
        {
             i++;
        }
        
       }
       i = 0;
       runn = 0;
    }
    */
