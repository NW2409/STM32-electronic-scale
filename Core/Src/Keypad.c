#include "Keypad.h"
#include <math.h>
char read_keypad (void)
{
	// Ma trận bàn phím: 4 hàng x 4 cột
    // Hàng 1: 'A', 'B', 'C', 'D'
    // Hàng 2: '3', '6', '9', '.'
    // Hàng 3: '2', '5', '8', '0'
    // Hàng 4: '1', '4', '7', '.'
	/* Make ROW 1 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));
		return 'A'; //1
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));
		return 'B'; //2
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));
		return 'C';// 3
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));
		return 'D';// A
	}

	/* Make ROW 2 LOW and all other ROWs HIGH */
	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));
		return '3';// 4
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));
		return '6';// 5
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));
		return '9';// 6
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));
		return '.';// B
	}


	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_SET);

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));
		return '2';//7
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));
		return '5';//8
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));
		return '8';//9
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));
		return '0';//C
	}


	HAL_GPIO_WritePin (R1_GPIO_Port, R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R2_GPIO_Port, R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R3_GPIO_Port, R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin (R4_GPIO_Port, R4_Pin, GPIO_PIN_RESET);

	if (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C1_GPIO_Port, C1_Pin)));
		return '1';//.
	}

	if (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C2_GPIO_Port, C2_Pin)));
		return '4';//0
	}

	if (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C3_GPIO_Port, C3_Pin)));
		return '7';//O
	}

	if (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)))
	{
		while (!(HAL_GPIO_ReadPin (C4_GPIO_Port, C4_Pin)));
		return '.';//D
	}

	return 0x01;
}


void get_keypad(float *result, float weight) {

    while (1) {
        char key = read_keypad();
        if (key!=0x01)
        {


        	if (key >= '0' && key <= '9') {
        		previous_result = *result;
				if (flag_decimal) {
					decimal_place *= 0.1;  // Giảm vị trí thập phân
					*result += (key - '0') * decimal_place; // Cập nhật phần thập phân
				}
				else {
					*result = (*result * 10) + (key - '0'); // Cập nhật phần nguyên
				}

			} else if (key == '.') {
				flag_decimal = 1; // Đặt cờ để bắt đầu nhập phần thập phân
			}
			else if (key == 'A') {
				if(flag_add == 0)
				{
					flag_add = 1;
					temp_price = 0.0 + ((*result) * weight);
					*result = 0.0;
					decimal_place = 1.0;
					flag_decimal = 0;
				}
				else
				{
					temp_price = temp_price + ((*result) * weight);
					*result = 0.0;
					decimal_place = 1.0;
					flag_decimal = 0;
				}

			}
			else if (key == 'B') {
				flag_total = 1;
				flag_add = 0;
			}
			else if (key == 'D') {  // Nếu là phím xóa
				if (flag_decimal && decimal_place < 1.0) {
					// Nếu đang nhập phần thập phân
					*result -= fmod(*result, decimal_place); // Loại bỏ chữ số thập phân cuối
					decimal_place *= 10; // Tăng lại độ chính xác
				} else {
					// Nếu đang ở phần nguyên
					*result = floor(*result / 10); // Loại bỏ chữ số cuối cùng
				}
			}
        	else if (key == 'C') {
                // Đặt lại tất cả giá trị về ban đầu
        		flag_total = 0;
                *result = 0.0;
                decimal_place = 1.0;
                flag_decimal = 0;
            }
			else
			{
				break;
			}
        }
        else
        {
        	break;
        }

    }
}



