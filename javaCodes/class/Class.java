import java.util.*;

public class Class {

    public static void main(String[] args) {
        int[] array1 = {8,70,45};
        int[] newArr = Arrays.copyOf(array1, 5);
        for (int x : newArr)
        {
            System.out.printf(x + " ");
        }

        System.out.println();

        String[] arr2 = {"Peter", "Alice", "dog", "67lily", "Bob", "wangming"};
        String[] newArr2 = Arrays.copyOfRange(arr2, 2, arr2.length);
        for (String x : newArr2)
        {
            System.out.print(x + " ");
        }
    }
}