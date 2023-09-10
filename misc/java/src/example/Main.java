/*
 * demo java package
 */

package example;

import library.*;

public class Main
{
	
	public static void main(String[] args)
	{
		System.out.println("main");
		Class c = new Class();
		c.Method();
		Library l = new Library();
		l.Method();
		System.out.println("exit");
	}
	
}
