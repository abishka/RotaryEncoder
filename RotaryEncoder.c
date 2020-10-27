#define e_pin1 10
#define e_pin2 11

#define encoder_pin1 digitalRead(e_pin1)
#define encoder_pin2 digitalRead(e_pin2)

void Rotary_Encoder(signed int *val,unsigned int step)
{
    static struct
    {
        unsigned char INC : 1;
        unsigned char DEC : 1;
        unsigned char two_seen0 : 1;
        unsigned char two_seen1 : 1;

    } Encoder_pos;

    if( !encoder_pin1 && !encoder_pin2 ) 
    {
        if (Encoder_pos.INC && Encoder_pos.two_seen1)
        {
            *val += step;
        }
        if (Encoder_pos.DEC && Encoder_pos.two_seen1)
        {
            *val -= step;
        }

        Encoder_pos.two_seen0 = 1;
        Encoder_pos.two_seen1 = 0;
        Encoder_pos.INC = 0;
        Encoder_pos.DEC = 0;
    }

    if( encoder_pin1 && encoder_pin2 )   
    {
        if (Encoder_pos.INC && Encoder_pos.two_seen0)
        {
            *val += step;
        }
        if (Encoder_pos.DEC && Encoder_pos.two_seen0)
        {

            *val -= step;
        }
        Encoder_pos.two_seen0 = 0;
        Encoder_pos.two_seen1 = 1;
        Encoder_pos.INC = 0;
        Encoder_pos.DEC = 0;
    }

    if( !encoder_pin1 && encoder_pin2 )   
    {
        if (Encoder_pos.two_seen0)
        {
            Encoder_pos.INC = 1;
        }
        if (Encoder_pos.two_seen1)
        {
            Encoder_pos.DEC = 1;
        }
    }

    if( encoder_pin1 && !encoder_pin2 )   
    {
        if (Encoder_pos.two_seen1)
        {
            Encoder_pos.INC = 1;
        }
        if (Encoder_pos.two_seen0)
        {
            Encoder_pos.DEC = 1;
        }
    }
}


