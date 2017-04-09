
import javax.crypto.Mac;  
import java.net.URLEncoder;
import java.security.InvalidKeyException;  
import javax.crypto.spec.SecretKeySpec;  
import org.apache.commons.lang.StringUtils;
  

public class URLEncoderHamc {  
	
    public static String standardURLEncoder(String data, String key) {  
        byte[] byteHMAC = null;  
        String urlEncoder = "" ;
        try {
            Mac mac = Mac.getInstance("HmacSHA1");  
            SecretKeySpec spec = new SecretKeySpec(key.getBytes(), "HmacSHA1");  
            mac.init(spec);  
            byteHMAC = mac.doFinal(data.getBytes());
            if(byteHMAC != null){
	            String oauth = new BASE64Encoder().encode(byteHMAC);
	            if(StringUtils.isNotBlank(oauth)){
	            	urlEncoder = URLEncoder.encode( oauth , "utf8"); 
	            }
            }
        } catch (InvalidKeyException e1) {  
            e1.printStackTrace();  
        } catch (Exception e2) {  
        	e2.printStackTrace();
        }
        return urlEncoder;
    }  
    
    public static void main(String[] args) {  
        try {  
            //需要加密的数据  
            String data = "http://open.weather.com.cn/data/?areaid=101010100&type=forecast_v&date=201410210236&appid=1234560";  
            //密钥  
            String key = "1f67f2_SmartWeatherAPI_11111111";  
            System.out.println(standardURLEncoder(data, key));
        } catch (Exception e) {  
            e.printStackTrace();  
        }  
    } 
}  
