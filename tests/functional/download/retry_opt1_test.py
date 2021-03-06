nzbget_options = ['HealthCheck=park', 'ArticleCache=500', 'DirectWrite=no']

def test_retry_small_retryfailed(nserv, nzbget):
	nzb_content = nzbget.load_nzb('small.nzb')
	nzb_content = nzb_content.replace('?3=6000:3000', '?3=6000:3000!2')
	hist = nzbget.download_nzb('small.bad3.nzb', nzb_content)
	assert hist['Status'] == 'FAILURE/HEALTH'
	nzbget.api.editqueue('HistoryRetryFailed', 0, '', [hist['NZBID']])
	hist = nzbget.wait_nzb('small.bad3.nzb')
	assert hist['Status'] == 'FAILURE/HEALTH'
	nzbget.api.editserver(2, True)
	nzbget.api.editqueue('HistoryRetryFailed', 0, '', [hist['NZBID']])
	hist = nzbget.wait_nzb('small.bad3.nzb')
	nzbget.api.editserver(2, False)
	assert hist['Status'] == 'SUCCESS/HEALTH'

def test_retry_medium_retryfailed(nserv, nzbget):
	nzb_content = nzbget.load_nzb('medium.nzb')
	nzb_content = nzb_content.replace('000000:500000', '000000:500000!2')
	hist = nzbget.download_nzb('medium.bad3.nzb', nzb_content)
	assert hist['Status'] == 'FAILURE/HEALTH'
	nzbget.api.editqueue('HistoryRetryFailed', 0, '', [hist['NZBID']])
	hist = nzbget.wait_nzb('medium.bad3.nzb')
	assert hist['Status'] == 'FAILURE/HEALTH'
	nzbget.api.editserver(2, True)
	nzbget.api.editqueue('HistoryRetryFailed', 0, '', [hist['NZBID']])
	hist = nzbget.wait_nzb('medium.bad3.nzb')
	nzbget.api.editserver(2, False)
	assert hist['Status'] == 'SUCCESS/HEALTH'
