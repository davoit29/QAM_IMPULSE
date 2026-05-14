import matplotlib.pyplot as plt
import pandas as pd

print("Чтение данных из results.csv...")
# Загружаем данные из файла
try:
    data = pd.read_csv('results.csv')
except FileNotFoundError:
    print("Ошибка: Файл results.csv не найден. Сначала запусти программу на C++!")
    exit()


plt.figure(figsize=(10, 6))


plt.plot(data['Variance'], data['BER_QPSK'], marker='o', linewidth=2, label='QPSK')
plt.plot(data['Variance'], data['BER_QAM16'], marker='s', linewidth=2, label='16-QAM')
plt.plot(data['Variance'], data['BER_QAM64'], marker='^', linewidth=2, label='64-QAM')


plt.yscale('log') 
plt.xlabel('Дисперсия шума (Noise Variance)')
plt.ylabel('Вероятность ошибки на бит (BER)')
plt.title('Зависимость BER от дисперсии шума для QAM')


plt.grid(True, which="both", ls="--", alpha=0.7)
plt.legend() 


plt.savefig('ber_plot.png', dpi=300, bbox_inches='tight')
print("График успешно сохранен как ber_plot.png!")


plt.show()