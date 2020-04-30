#include <EEPROM.h>
#include <string.h>

#define ADC_CELL_1 A0
#define ADC_CELL_2 A1
#define ADC_CELL_3 A2
#define ADC_CELL_4 A3

#define CELL_1 0
#define CELL_2 1
#define CELL_3 2
#define CELL_4 3

unsigned short CELL[4] = {
  CELL_1,
  CELL_2,
  CELL_3,
  CELL_4,
};
unsigned short ADC_CHANNEL[4] = {
  ADC_CELL_1,
  ADC_CELL_2,
  ADC_CELL_3, 
  ADC_CELL_4,
};


#define ADC_REF 5.00
#define ADC_MAX_RAW 1023


float OFFSET_CELL_1 = 0.03;
float OFFSET_CELL_2 = 0.40;
float OFFSET_CELL_3 = 0.69;
float OFFSET_CELL_4 = 1.42;

float OFFSET[4] = {
  OFFSET_CELL_1,
  OFFSET_CELL_2,
  OFFSET_CELL_3,
  OFFSET_CELL_4,
};

float GAIN_CELL_1 = 1.01;
float GAIN_CELL_2 = 1.40;
float GAIN_CELL_3 = 1.69;
float GAIN_CELL_4 = 2.14;

float GAIN[4] = {
  GAIN_CELL_1,
  GAIN_CELL_2,
  GAIN_CELL_3,
  GAIN_CELL_4,
};


unsigned short FILTER_RANK = 5;

void setup()
{
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ADC_CELL_1, INPUT);
  pinMode(ADC_CELL_2, INPUT);
  pinMode(ADC_CELL_3, INPUT);
  pinMode(ADC_CELL_4, INPUT);

  save_profile();
  print_profile();
  Serial.println("");
  load_profile();
  print_profile();
//  print_eeprom();
//  f2c();
  delay(5000);
}

void loop()
{
//  delay(1000);
//  Serial.print("CELL 1: ");
//  Serial.print(get_cell_voltage_processed(CELL_1));
//  Serial.println("V");
//  Serial.print("CELL 2: ");
//  Serial.print(get_cell_voltage_processed(CELL_2));
//  Serial.println("V");
//  Serial.print("CELL 3: ");
//  Serial.print(get_cell_voltage_processed(CELL_3));
//  Serial.println("V");
//  Serial.print("CELL 4: ");
//  Serial.print(get_cell_voltage_processed(CELL_4));
//  Serial.println("V");
//  Serial.println("");
}

unsigned int get_cell_voltage_raw(unsigned short cell)
{
  return analogRead(ADC_CHANNEL[cell]);
}

float get_cell_voltage(unsigned short cell)
{
  return (((ADC_REF) * ((float)(analogRead(ADC_CHANNEL[cell])))) / ((float)(ADC_MAX_RAW)));
}

float get_cell_voltage_processed(unsigned short cell)
{
  float voltage_sum = 0;
  float average_voltage;
  float processed_voltage;
  
  unsigned char filter_rank_counter;
  
  for(filter_rank_counter = 0; filter_rank_counter < FILTER_RANK; filter_rank_counter ++)
  {
    voltage_sum += get_cell_voltage(cell);
  }

  average_voltage = voltage_sum / FILTER_RANK;
  processed_voltage = average_voltage * GAIN[cell];
  processed_voltage += OFFSET[cell];
  
  return processed_voltage;
}

unsigned short print_eeprom()
{
  unsigned int i = 0;
  unsigned char n;
  for(i = 0; i < 256; i ++)
  {
    n = EEPROM.read(i);
    Serial.print("0x");
    Serial.print(n < 16 ? "0" : "");
    Serial.print(n, HEX);
    Serial.print(" ");
    if ((i + 1) % 16 == 0)
    {
      Serial.println("");
    }
  }
}

void f2c(void)
{
  unsigned char char_buffer[sizeof(float)];
  Serial.print("SIZE CHAR: ");
  Serial.println(sizeof(char_buffer));

  Serial.println(GAIN_CELL_1, HEX);
  memcpy(char_buffer, &GAIN_CELL_1, sizeof(float));
  for(unsigned char c = 0; c < sizeof(float); c ++)
  {
    Serial.println(char_buffer[c]);
  }
  float f;
  memcpy(&f, char_buffer, sizeof(float));
  Serial.println(f);
}

unsigned short save_profile(void)
{
  unsigned char char_buffer[sizeof(float)];
  unsigned char eeprom_address = 0;
  
  memcpy(char_buffer, &OFFSET_CELL_1, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &GAIN_CELL_1, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &OFFSET_CELL_2, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &GAIN_CELL_2, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &OFFSET_CELL_3, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &GAIN_CELL_3, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &OFFSET_CELL_4, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &GAIN_CELL_4, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }
  
  memcpy(char_buffer, &FILTER_RANK, sizeof(float));
  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    EEPROM.write(eeprom_address, char_buffer[index]);
    eeprom_address ++;
  }

  return 0;
}

unsigned short load_profile(void)
{
  unsigned char char_buffer[sizeof(float)];
  unsigned char eeprom_address = 0;

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&OFFSET_CELL_1, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&GAIN_CELL_1, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&OFFSET_CELL_2, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&GAIN_CELL_2, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&OFFSET_CELL_3, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&GAIN_CELL_3, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&OFFSET_CELL_4, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&GAIN_CELL_4, char_buffer, sizeof(float));

  for(unsigned char index = 0; index < sizeof(float); index ++)
  {
    char_buffer[index] = EEPROM.read(eeprom_address);
    eeprom_address ++;
  }
  memcpy(&FILTER_RANK, char_buffer, sizeof(float));
  
  return 0;
}


void print_profile(void)
{
  Serial.println(OFFSET_CELL_1);
  Serial.println(GAIN_CELL_1);
  Serial.println(OFFSET_CELL_2);
  Serial.println(GAIN_CELL_2);
  Serial.println(OFFSET_CELL_3);
  Serial.println(GAIN_CELL_3);
  Serial.println(OFFSET_CELL_4);
  Serial.println(GAIN_CELL_4);
  Serial.println(FILTER_RANK);
}
