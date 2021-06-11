from bs4 import BeautifulSoup
import requests
from urllib.request import urlopen as uReq
import time

def getUrl (searchTerm):
	template = 'https://www.amazon.com.br/s?k={}'
	searchTerm = searchTerm.replace(' ', '+')
	return template.format(searchTerm)

def getItem (item):
	gotContent = False

	while (gotContent == False):
		url = getUrl(item)
		print ('Aguarde...')
		html_text = requests.get(url).text
		soup = BeautifulSoup (html_text, 'lxml')
		products = soup.find_all ('div', class_ = 'sg-col-4-of-12 s-result-item s-asin sg-col-4-of-16 sg-col sg-col-4-of-20')
		if (products != []):
			gotContent = True\

	productList = []

	for product in products:
		name = product.find('span', class_ = 'a-size-base-plus a-color-base a-text-normal').text
		price = True

		productLink = ""

		for a in product.find_all('a', href=True):
			productLink = a['href']
			break

		try:
			priceWhole = product.find ('span', class_ = 'a-price-whole').text
			priceFraction = product.find ('span', class_ = 'a-price-fraction').text
		except:
			price = False

		if price == True:
			completePrice = priceWhole + priceFraction
			currentProduct = (name, completePrice, productLink, "amazon")
			productList.append (currentProduct)
			# print (name)
			# print (priceWhole + priceFraction)
	return tuple(productList)

#print(getItem ('Iphone X'))
