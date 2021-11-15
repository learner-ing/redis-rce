# redis-rce
windows redis主从复制
具体分析请看[redis主从复制的一些利用](https://djhons.com/2021/10/29/61.html)

请不要用于未授权的渗透测试，如果用于未授权的渗透测试与本人无关。

**1、在测试环境中导致了redis服务崩溃，目前已修好，但不保证在实际环境中不会出现这种问题，请小心使用。已知redis 4.x的alpha版本还不支持module，所以肯定会导致服务崩溃。**
**2、在windows server中会出现和redis6一样找不到动态链接库的情况，目前不知道是什么原因，猜测和dll的权限可能有关系，因为redis在加载dll时是使用的network权限。**
