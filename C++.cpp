#include <iostream>
#include <cstring>
#include <iomanip>

const int N = 5;
struct student {
    char name[8];
    short age;
    float score;
    char remark[200];
};
student old_s[N], new_s[N];
int pack_student_bytebybyte(student* s, int sno, char *buf) {
    int offset = 0;
    for (int i = 0; i < sno; i++) {
        for (int j = 0; j < 8; j++) {
            buf[offset++] = s[i].name[j];
        }
        buf[offset++] = (char)(s[i].age & 0xFF);
        buf[offset++] = (char)((s[i].age >> 8) & 0xFF);
        unsigned char *p = (unsigned char*)(&s[i].score);
        for (int j = 0; j < sizeof(float); j++) {
            buf[offset++] = p[j];
        }
        for (int j = 0; j < 200; j++) {
            buf[offset++] = s[i].remark[j];
        }
    }
    return offset;
}
int pack_student_whole(student* s, int sno, char *buf) {
    int offset = 0;
    for (int i = 0; i < sno; i++) {
        strcpy(buf + offset, s[i].name);
        offset += 8;
        *(short*)(buf + offset) = s[i].age;
        offset += sizeof(short);
        *(float*)(buf + offset) = s[i].score;
        offset += sizeof(float);
        strcpy(buf + offset, s[i].remark);
        offset += 200;
    }
    return offset;
}
int restore_student(char *buf, int len, student* s) {
    int offset = 0, count = 0;
    while (offset < len) {
        for (int i = 0; i < 8; i++) {
            s[count].name[i] = buf[offset++];
        }
        s[count].age = *(short*)(buf + offset);
        offset += sizeof(short);
        s[count].score = *(float*)(buf + offset);
        offset += sizeof(float);
        // 解压备注
        for (int i = 0; i < 200; i++) {
            s[count].remark[i] = buf[offset++];
        }
        count++;
    }
    return count;
}
void input_student_data() {
    for (int i = 0; i < N; i++) {
        std::cout << "Input the " << i + 1 << "-th student's name, age, score and remark:\n";
        std::cin >> old_s[i].name >> old_s[i].age >> old_s[i].score;
        std::cin.ignore();
        std::cin.getline(old_s[i].remark, 200);
    }
}
int main() {
    input_student_data();
    char message[2000];
    int total_len = 0;
    total_len += pack_student_bytebybyte(old_s, 2, message);
    total_len += pack_student_whole(old_s + 2, 3, message + total_len);
    restore_student(message, total_len, new_s);
    for (int i = 0; i < N; i++) {
        std::cout << "Student " << i + 1 << ": Name = " << new_s[i].name
                  << ", Age = " << new_s[i].age
                  << ", Score = " << new_s[i].score
                  << ", Remark = " << new_s[i].remark << "\n";
    }
    std::cout << "After zip: " << sizeof(old_s) << "\n";
    std::cout << "Sizeof zip: " << total_len << "\n";
    std::cout << "the first 20 Bytes content of message: ";
    for (int i = 0; i < 20; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)message[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
