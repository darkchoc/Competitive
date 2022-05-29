import pandas as pd
import json
from uaparser import UAParser

file_name = "data/r2a_new.csv"

df = pd.read_csv(file_name)
print("total rows")
print(df.shape)


def constructR2AMap(df):
	df['publisher_url'] = df['publisher_url'].apply(processUrl)
	newMap = {}
	for i, row in df.iterrows():
		url = row['publisher_url']
		url = "breqUrl/" + url
		click = row['clicks']
		while True:
			if url not in newMap:
				newMap[url] = {"ac": 0.0, "ap": 0.0}
			newMap["ap"] += 1.0
			if click:
				newMap["ac"] += 1.0
			if '/' in url:
				url = url[:url.rfind('/')]
			else:
				break
	return newMap



r2amap = constructR2AMap(df)

# Ignore first n rows
ignore = 0
df = df.iloc[ignore:]
print("Number of rows after ignoring first {} rows: {} and adclicks = {}".format(ignore, df.shape, df[df['clicks']==1].shape))


#sample
# sample_fraction=0.8
# df = df.sample(frac=sample_fraction, random_state=1)
# print("Number of rows after sampling: {} and adclicks = {}".format(df.shape, df[df['clicks']==1].shape))

# train_fraction = 0.75
# train = df.sample(frac=train_fraction, random_state=1)
# test = df.drop(train.index)

# print("Number of rows in train: " + str(train.shape) + " and adclicks= " + str(train[train['clicks']==1].shape))
# print("Number of rows in test: " + str(test.shape) + " and adclicks= " + str(test[test['clicks']==1].shape))

PROPERTIES = [
    'stream.3gp.h264.level10', 'isFeedReader', 'js.touchEvents', 'csd', 'html.canvas', 'js.webGl', 'browserVersion', 'flashCapable', 'isMobilePhone', 'osRim', 'stream.3gp.h264.level11', 'js.modifyDom', 'js.geoLocation', '3gp.aac.lc', '3gp.h264.level13', 'mp3', 'lte', 'developerPlatform', 'html.inlinesvg', '3gp.h264.level10', 'stream.3gp.aac.lc', 'id', 'isEReader', 'usableDisplayHeight', 'markup.xhtmlMp11', 'stream.mp4.h264.level13', 'amr', 'browserRenderingEngine', 'jsr37', 'jsr139', 'nfc', 'uriSchemeSmsTo', 'css.transitions', 'cookieSupport', 'html.svg', 'developerPlatformVersion', 'css.transforms', 'stream.httpLiveStreaming', 'vCardDownload', 'js.sessionStorage', 'uriSchemeSms', 'osWindowsMobile', 'osProprietary', 'osAndroid', 'primaryHardwareType', '3gp.amr.wb', 'js.supportEventListener', 'hsdpa', 'jsr30', 'mp4.h264.level11', 'markup.wml1', 'js.webSqlDatabase', 'displayColorDepth', 'isDownloader', 'mobileDevice', 'image.Gif87', 'isTablet', 'js.deviceMotion', 'midiPolyphonic', 'memoryLimitEmbeddedMedia', 'midiMonophonic', 'displayWidth', '3gp.h264.level12', 'drmOmaForwardLock', 'osWebOs', 'js.localStorage', 'qcelpInVideo', '3gp.amr.nb', 'qcelp', 'touchScreen', 'hscsd', 'isMediaPlayer', 'mp4.h264.level13', 'stream.3gp.amr.nb', 'js.deviceOrientation', 'displayPpi', 'isBrowser', 'js.supportEvents', 'isGamesConsole', 'stream.3gp.h263', 'isFilter', 'hspaEvolved', 'gprs', 'isChecker', 'markup.xhtmlMp12', 'osVersion', 'browserName', 'memoryLimitDownload', 'js.xhr', 'isMasqueradingAsDesktop', 'osSymbian', 'usableDisplayWidth', 'manufacturer', 'drmOmaSeparateDelivery', 'html.video', 'js.webSockets', 'js.modifyCss', 'stream.mp4.aac.lc', 'stream.3gp.amr.wb', 'js.supportBasicJavaScript', 'aac', 'vendor', 'isApp', 'stream.3gp.h264.level13', 'js.applicationCache', 'js.supportConsoleLog', 'js.webWorkers', 'wmv', 'edge', 'cldc', 'model', 'displayHeight', 'osWindowsRt', 'diagonalScreenSize', 'markup.xhtmlMp10', 'js.json', 'image.Jpg', '3gp.h263', 'drmOmaCombinedDelivery', '3gp.h264.level10b', 'stream.3gp.h264.level12', 'css.animations', 'supportsClientSide', 'jqm', 'https', 'memoryLimitMarkup', 'stream.mp4.h264.level11', 'camera', 'yearReleased', '3gp.h264.level11', 'lteAdvanced', 'osWindowsPhone', 'js.querySelector', 'isTV', 'devicePixelRatio', 'umts', 'uriSchemeTel', 'osName', 'midp', 'osBada', 'image.Png', 'html.audio', 'jsr118', 'isSpam', 'js.indexedDB', 'marketingName', 'mp4.aac.lc', 'image.Gif89a', 'isSetTopBox', 'stream.3gp.h264.level10b', 'osiOs', 'css.columns', 'isRobot', 'markup.xhtmlBasic10'
]

parser = UAParser()

for prop in PROPERTIES:
    df[prop] = df['user_agent'].apply(parser.getUAProperty, args=(prop,))

def strip(url, pattern):
    if url.startswith(pattern):
        return url[len(pattern):]
    else:
        return url

def processUrl(url):
    url = url.split('?')[0]
    url = url.split('#')[0]
    url = strip(url,'http://')
    url = strip(url,'https://')
    url = strip(url,'android-app://')
    url = url.replace(' ', '')
    url = url.lower()
    url = ''.join(e for e in url if (e.isalnum() or e=='/' or e=='.' or e=='-'))
    url = url.rstrip('/')
    url = url + "/"
    return url

def getR2A(domain):
    key = "breqUrl/" + domain + "/"
    while True:
        if key in r2amap:
            if r2amap[key]["ac"] > 0.0 or r2amap[key]["ap"] > 10:
                return r2amap[key]["ac"]/r2amap[key]["ap"]
        if '/' in key:
            key = key[:key.rfind('/')]
        else:
            break
    return 0.0

def getKeywordClicks(url):
    key = "breqUrl/" + url + "/"
    while True:
        if key in r2amap:
            if r2amap[key]["ac"] > 0.0 or r2amap[key]["ap"] > 10:
                return r2amap[key]["ap"]
        if '/' in key:
            key = key[:key.rfind('/')]
        else:
            break
    return 0.0


df['publisher_url'] = df['publisher_url'].apply(processUrl)
df['clicks'].fillna(0, inplace=True)
df['refering_domain'].fillna("", inplace=True)
df['domain_r2a'] = df['domain_name'].apply(getR2A)
df['url_r2a'] = df['publisher_url'].apply(getR2A)
df['url_views'] = df['publisher_url'].apply(getKeywordClicks)
df.to_csv('data/r2a_media_parsed.csv', index=False)
