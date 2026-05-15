import matplotlib.pyplot as plt
import pandas as pd



try:
    data = pd.read_csv('results.csv')
except FileNotFoundError:
    print("Ошибка" \
    "")
    exit()


plt.figure(figsize=(10, 6))


plt.plot(data['Variance'], data['BER_QPSK'], linewidth=2, label='QPSK',color = 'black')
plt.plot(data['Variance'], data['BER_QAM16'], linewidth=2, label='16-QAM' ,color = 'red')
plt.plot(data['Variance'], data['BER_QAM64'], linewidth=2, label='64-QAM',color = 'green')


plt.yscale('log') 
plt.xlabel('Дисперсия шума ')
plt.ylabel('BER')
plt.title('Зависимость BER от дисперсии шума ')


plt.grid(True, which="both", ls="--", alpha=0.7)
plt.legend() 


plt.savefig('ber_plot.png', dpi=300, bbox_inches='tight')
print("График готов")


plt.show()