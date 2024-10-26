import java.util.Random;
import java.util.Scanner;

public class GuessingGame {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rnd = new Random();
        boolean play = true;

        while (play) {
            int target = rnd.nextInt(20) + 1;
            boolean guessed = false;

            System.out.println("猜数字游戏开始！你有三次机会猜一个1到20之间的整数。");

            for (int i = 0; i < 3; i++) {
                System.out.print("请输入你的猜测：");
                int guess = sc.nextInt();

                if (guess == target) {
                    System.out.println("恭喜你，猜对了");
                    guessed = true;
                    break;
                } else {
                    System.out.println("猜错了！");
                }
            }

            if (!guessed) {
                System.out.println("很遗憾，你没有猜对");
            }

            System.out.print("你想继续游戏吗？输入 'y' 继续，输入其他任意键退出：");
            String resp = sc.next();
            play = resp.equalsIgnoreCase("y");
        }

        System.out.println("游戏结束，谢谢参与！");
        sc.close();
    }
}