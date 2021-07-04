
// Figure 19.1 ~ 19.4 diagrams without code


// figure-19-04.java, Java program illustrating a DNS lookup

/**
  * Usage: java DNSLookUp <IP name>
  * i.e. java DNSLookUp www.wiley.com
*/
public class DNSLookUp {
	public static void main(String[] args) {
		InetAddress hostAddress;

		try {
			hostAddress = InetAddress.getByName(args[0]);
			System.out.println(hostAddress.getHostAddress());
		}
		catch (UnknownHostException uhe) {
		    System.err.println("Unknown host: " + args[0]);
		}
	}
}


// Figure 19.5 ~ 19.11 diagrams without code