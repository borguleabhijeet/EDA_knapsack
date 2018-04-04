clear all;
close all;
load('output.txt')

hold on

plot(output(:,2),'r','LineWidth',2)
hold on
plot(output(:,3),'b','LineWidth',2)
hold on
plot(output(:,4),'g','LineWidth',2)
xlabel('Iteration')
ylabel('Profit')
legend('Profit','Weight','Average Profit')
