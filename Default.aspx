<%@ Page Language="C#" %>

<script runat="server">
    protected void OnClick(object sender, EventArgs e)
    {
        System.Net.Sockets.Socket soc = new System.Net.Sockets.Socket(System.Net.Sockets.AddressFamily.InterNetwork, System.Net.Sockets.SocketType.Stream, System.Net.Sockets.ProtocolType.Tcp);
        System.Net.IPAddress ipAdd = System.Net.IPAddress.Parse("192.168.1.9");
        System.Net.IPEndPoint remoteEP = new System.Net.IPEndPoint(ipAdd, 3300);
        soc.Connect(remoteEP);
        byte[] byData = System.Text.Encoding.ASCII.GetBytes("T\n");
        soc.Send(byData);
        soc.Disconnect(false);
        soc.Close();
    }
</script>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Air Toggle</title>
    <style>
* {
    box-sizing: border-box
} 

.container {
    padding: 10px;
    margin: 0 auto;
    max-width: 500px;
}

.button {
    margin: 10px 0;
    padding: 100px;
    width: 100%;
    font-size: 42px;
}
    </style>
</head>
<body>
    <form id="form1" runat="server">
    <div class="container">
    <asp:Button Text="Toggle" OnClick="OnClick" CssClass="button" runat="server"/>
    </div>
    </form>
</body>
</html>
